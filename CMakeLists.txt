cmake_minimum_required(VERSION 3.28)
project(OOHD VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 26)

# Add source files
set(SOURCES
        src/DatabaseObject.cpp
        src/Query.cpp
        src/QueryResult.cpp
        src/OOHD.cpp
        src/OOHDQuery.cpp
        src/main.cpp
)

# Add header files
set(HEADERS
        include/DatabaseObject.hpp
        include/Query.hpp
        include/QueryResult.hpp
        include/OOHDQuery.hpp
        include/OOHD.hpp
        include/OOHDList.hpp
        include/DynamicObject.hpp
)

# Create the executable
add_executable(oohd ${SOURCES} ${HEADERS})

# Specify include directories
target_include_directories(oohd PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Enable warnings
if(MSVC)
    target_compile_options(oohd PRIVATE /W4)
else()
    target_compile_options(oohd PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Add a custom target for running the executable
add_custom_target(run
        COMMAND oohd
        DEPENDS oohd
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

# Optionally, add testing
# enable_testing()
# add_test(NAME OOHDTest COMMAND oohd)