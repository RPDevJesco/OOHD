#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <fstream>

class Query;
class OOHD;

class DatabaseObject : public std::enable_shared_from_this<DatabaseObject> {
private:
    std::string id;
    std::string type;
    std::weak_ptr<DatabaseObject> parent;
    std::vector<std::shared_ptr<DatabaseObject>> children;
    std::unordered_map<std::string, std::string> attributes;

    static void encryptString(std::string& data, const std::string& key);
    static void decryptString(std::string& data, const std::string& key);

public:
    DatabaseObject(const std::string& id, const std::string& type);
    virtual ~DatabaseObject() = default;

    std::string getId() const;
    std::string getType() const;
    void setParent(std::shared_ptr<DatabaseObject> newParent);
    void addChild(std::shared_ptr<DatabaseObject> child);
    void setAttribute(const std::string& key, const std::string& value);
    std::string getAttribute(const std::string& key) const;
    virtual void display() const;
    virtual bool matchesQuery(const Query& query) const;

    // Serialization methods
    void serialize(std::ofstream& out) const;
    static std::shared_ptr<DatabaseObject> deserialize(std::ifstream& in);

    friend class OOHD;
};