#include "OOHD.hpp"
#include <stdexcept>
#include <fstream>
#include <iostream>

OOHD::OOHD() : root(std::make_shared<DatabaseObject>("root", "root")) {
    objectMap["root"] = root;
    typeIndex["root"].push_back(root);
}

void OOHD::addObject(const std::string& parentId, std::shared_ptr<DatabaseObject> object) {
    auto parentIt = objectMap.find(parentId);
    if (parentIt == objectMap.end()) throw std::runtime_error("Parent object not found");

    parentIt->second->addChild(object);
    objectMap[object->getId()] = object;
    typeIndex[object->getType()].push_back(object);

    for (const auto& attr : object->attributes) {
        attributeIndex[attr.first][attr.second].push_back(object);
    }

    queryCache.clear();
}

std::shared_ptr<DatabaseObject> OOHD::getObject(const std::string& id) const {
    auto it = objectMap.find(id);
    if (it != objectMap.end()) return it->second;
    throw std::runtime_error("Object not found");
}

void OOHD::displayHierarchy(const std::shared_ptr<DatabaseObject>& node, int depth) const {
    std::string indent(depth * 2, ' ');
    node->display();
    for (const auto& child : node->children) {
        displayHierarchy(child, depth + 1);
    }
}

void OOHD::displayFullHierarchy() const {
    displayHierarchy(root);
}

QueryResult OOHD::query(const Query& query) {
    if (query.getLimit() == 0) {
        auto cacheIt = queryCache.find(query.hash());
        if (cacheIt != queryCache.end()) {
            return cacheIt->second;
        }
    }

    std::vector<std::shared_ptr<DatabaseObject>> results;
    for (const auto& [id, obj] : objectMap) {
        bool matches = query.evaluate(*obj);

        if (matches) {
            results.push_back(obj);
        }
    }

    QueryResult queryResult(std::move(results));

    // Only cache queries without LIMIT
    if (query.getLimit() == 0) {
        queryCache[query.hash()] = queryResult;
    }

    return queryResult;
}

void OOHD::saveToFile(const std::string& filename) const {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }

    // Write the number of objects
    size_t objectCount = objectMap.size();
    out.write(reinterpret_cast<const char*>(&objectCount), sizeof(size_t));

    // Serialize all objects
    for (const auto& pair : objectMap) {
        pair.second->serialize(out);
    }

    out.close();
}

OOHD OOHD::loadFromFile(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }

    OOHD database;

    // Read the number of objects
    size_t objectCount;
    in.read(reinterpret_cast<char*>(&objectCount), sizeof(size_t));

    // Deserialize all objects
    for (size_t i = 0; i < objectCount; ++i) {
        auto obj = DatabaseObject::deserialize(in);
        database.objectMap[obj->getId()] = obj;
        database.typeIndex[obj->getType()].push_back(obj);
        for (const auto& attr : obj->attributes) {
            database.attributeIndex[attr.first][attr.second].push_back(obj);
        }
    }

    // Link children
    for (auto& pair : database.objectMap) {
        auto& obj = pair.second;
        std::vector<std::shared_ptr<DatabaseObject>> actualChildren;
        for (const auto& placeholder : obj->children) {
            actualChildren.push_back(database.objectMap[placeholder->getId()]);
        }
        obj->children = actualChildren;
    }

    // Set the root
    database.root = database.objectMap["root"];

    in.close();
    return database;
}