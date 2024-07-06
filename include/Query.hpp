#pragma once

#include <vector>
#include <functional>
#include <string>

class DatabaseObject; // Forward declaration

class Query {
public:
    enum class Operator { AND, OR, NOT };

private:
    std::vector<std::function<bool(const DatabaseObject&)>> conditions;
    std::vector<Operator> operators;
    mutable size_t cachedHash = 0;
    mutable bool hashComputed = false;

public:
    Query& byType(const std::string& type);
    Query& byAttribute(const std::string& key, const std::string& value);
    Query& byCustomCondition(std::function<bool(const DatabaseObject&)> customCondition);
    Query& setOperator(Operator op);
    Query& orQuery();
    Query& andQuery();
    Query& notQuery();

    bool evaluate(const DatabaseObject& obj) const;
    size_t hash() const;
    bool operator==(const Query& other) const;

private:
    void invalidateHash();
};