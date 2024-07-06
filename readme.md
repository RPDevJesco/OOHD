# Object-Oriented Hierarchical Database (OOHD)

## Project Overview

The Object-Oriented Hierarchical Database (OOHD) is a C++ implementation that combines the hierarchical structure of tree-based databases with the flexibility and richness of object-oriented databases. This design allows each record to have a single parent, maintaining a clear hierarchical structure, while storing data as objects to support complex data types and relationships.

## Key Features

1. **Hierarchical Structure**: Data is organized in a tree-like hierarchy, where each record has a single parent and potentially multiple children.

2. **Object-Oriented Data Storage**: Each node in the hierarchy represents an object, storing complex data types and supporting object-oriented principles such as encapsulation and inheritance.

3. **Flexible Schema**: Supports a flexible schema, enabling different types of objects to coexist within the hierarchy.

4. **Query System**: Implements a flexible query system that allows for complex searches based on object types, attributes, and hierarchical relationships.

5. **Caching**: Includes a query cache to improve performance for repeated queries.

6. **Serialization**: Supports saving the database to a file and loading it back, with basic encryption to protect the data.

## Project Structure

The project is organized into the following main components:

- `DatabaseObject`: Represents a node in the hierarchical structure.
- `Query`: Implements the query system for searching the database.
- `QueryResult`: Handles the results of queries, including sorting and limiting.
- `OOHD`: The main database class that manages the overall structure and operations.

## Building and Running

This project uses CMake for building. To build and run the project:

1. Create a build directory: `mkdir build && cd build`
2. Run CMake: `cmake ..`
3. Build the project: `make`
4. Run the executable: `./oohd`

## Future Enhancements

While the current implementation provides a solid foundation for an object-oriented hierarchical database, there are several areas where it could be expanded and improved:

1. **Advanced Querying**: Implement more complex query operations, such as joins between different object types.

2. **Indexing**: Add support for indexing to improve query performance, especially for large datasets.

3. **Concurrency**: Implement thread-safety and support for concurrent operations on the database.

4. **Transactions**: Add support for ACID transactions to ensure data integrity.

5. **Persistence**: Improve the current serialization method, possibly using a more standardized format like Protocol Buffers.

6. **Security**: Enhance the encryption method used for file storage, possibly integrating with a robust encryption library.

7. **API**: Develop a more comprehensive API for interacting with the database, possibly including a query language.

8. **Inheritance**: Implement true object-oriented inheritance for database objects.

9. **Event System**: Add an event system to allow for triggers and reactive programming paradigms.

10. **Distributed Operation**: Extend the system to support distributed databases and operations.

11. **Visualization**: Create tools for visualizing the hierarchical structure of the database.

12. **Performance Optimization**: Conduct thorough performance testing and optimize critical paths.