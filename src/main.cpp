#include "OOHD.hpp"
#include <iostream>
#include <chrono>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

int main() {
    OOHD database;

    // Add sample data
    auto dept1 = std::make_shared<DatabaseObject>("dept1", "department");
    dept1->setAttribute("name", "Engineering");
    database.addObject("root", dept1);

    auto dept2 = std::make_shared<DatabaseObject>("dept2", "department");
    dept2->setAttribute("name", "Marketing");
    database.addObject("root", dept2);

    auto emp1 = std::make_shared<DatabaseObject>("emp1", "employee");
    emp1->setAttribute("name", "John Doe");
    emp1->setAttribute("position", "Software Engineer");
    database.addObject("dept1", emp1);

    auto emp2 = std::make_shared<DatabaseObject>("emp2", "employee");
    emp2->setAttribute("name", "Jane Smith");
    emp2->setAttribute("position", "Team Lead");
    database.addObject("dept1", emp2);

    auto emp3 = std::make_shared<DatabaseObject>("emp3", "employee");
    emp3->setAttribute("name", "Bob Johnson");
    emp3->setAttribute("position", "Marketing Specialist");
    database.addObject("dept2", emp3);

    std::cout << "Full Hierarchy:" << std::endl;
    database.displayFullHierarchy();

    // Get the current working directory
    fs::path cwd = fs::current_path();
    fs::path dbPath = cwd / "database.hdb";

    std::cout << "\nAttempting to save database to: " << dbPath << std::endl;

    try {
        // Save the database to a file
        database.saveToFile(dbPath.string());
        std::cout << "Database saved successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error saving database: " << e.what() << std::endl;
        return 1;
    }

    if (fs::exists(dbPath)) {
        std::cout << "File size: " << fs::file_size(dbPath) << " bytes" << std::endl;
    } else {
        std::cerr << "Error: File was not created." << std::endl;
        return 1;
    }

    // Example query with sorting and limiting
    std::cout << "\nQuerying employees, sorted by name and limited to 2 results:" << std::endl;
    Query employeeQuery;
    employeeQuery.byType("employee");

    auto start = std::chrono::high_resolution_clock::now();
    auto queryResult = database.query(employeeQuery)
            .sort([](const DatabaseObject& a, const DatabaseObject& b) {
                return a.getAttribute("name") < b.getAttribute("name");
            })
            .limit(2);
    auto end = std::chrono::high_resolution_clock::now();

    for (const auto& obj : queryResult.getResults()) {
        obj->display();
    }

    std::cout << "Query execution time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds" << std::endl;

    // Demonstrate caching
    std::cout << "\nRunning the same query again to demonstrate caching:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    queryResult = database.query(employeeQuery)
            .sort([](const DatabaseObject& a, const DatabaseObject& b) {
                return a.getAttribute("name") < b.getAttribute("name");
            })
            .limit(2);
    end = std::chrono::high_resolution_clock::now();

    for (const auto& obj : queryResult.getResults()) {
        obj->display();
    }

    std::cout << "Cached query execution time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds" << std::endl;

    return 0;
}