#include "OOHD.hpp"
#include "OOHDList.hpp"
#include "DynamicObject.hpp"
#include <iostream>
#include <iomanip>

void createSampleDatabase(OOHD& database) {
    auto emp1 = std::make_shared<DynamicObject>("emp1", "employee");
    emp1->setAttribute("name", "John Doe");
    emp1->setAttribute("position", "Software Engineer");
    emp1->setAttribute("salary", 75000);
    database.addObject("root", emp1);

    auto emp2 = std::make_shared<DynamicObject>("emp2", "employee");
    emp2->setAttribute("name", "Jane Smith");
    emp2->setAttribute("position", "Team Lead");
    emp2->setAttribute("salary", 95000);
    database.addObject("root", emp2);

    auto emp3 = std::make_shared<DynamicObject>("emp3", "employee");
    emp3->setAttribute("name", "Bob Johnson");
    emp3->setAttribute("position", "Software Engineer");
    emp3->setAttribute("salary", 72000);
    database.addObject("root", emp3);
}

void printObjects(const OOHDList& objects) {
    if (objects.empty()) {
        std::cout << "No objects found." << std::endl;
        return;
    }

    // Print header
    for (const auto& attr : objects[0]->attributes) {
        std::cout << std::setw(15) << attr.first << " | ";
    }
    std::cout << std::endl;
    std::cout << std::string(objects[0]->attributes.size() * 18, '-') << std::endl;

    // Print rows
    for (const auto& obj : objects) {
        for (const auto& attr : obj->attributes) {
            std::cout << std::setw(15) << obj->getAttribute<std::string>(attr.first) << " | ";
        }
        std::cout << std::endl;
    }
}

int main() {
    OOHD database;
    createSampleDatabase(database);

    // Set the database for OOHDList
    OOHDList::setDatabase(database);

    // Now we can use the embedded query syntax
    OOHDList objectList;

    try {
        objectList = "SELECT name, position, salary FROM employee";
        std::cout << "All employees:" << std::endl;
        printObjects(objectList);

        objectList = "SELECT name, position FROM employee WHERE position = 'Software Engineer'";
        std::cout << "\nSoftware Engineers:" << std::endl;
        printObjects(objectList);

        objectList = "SELECT name, salary FROM employee WHERE salary > '80000'";
        std::cout << "\nEmployees with salary over 80000:" << std::endl;
        printObjects(objectList);

        objectList = "SELECT name FROM employee LIMIT 2";
        std::cout << "\nFirst two employees:" << std::endl;
        printObjects(objectList);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}