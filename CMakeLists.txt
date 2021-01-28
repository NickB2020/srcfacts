# @file CMakeLists.txt
# 
# CMake files for the srcFacts project

# Can be run by any version of CMake >= this
cmake_minimum_required(VERSION 3.10)

# project info
project(srcFacts)

# C++17 standard
set(CMAKE_CXX_STANDARD 17)

# Use Release build type if not specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Source files for the main program srcFacts
set(SOURCE srcFacts.cpp refillBuffer.cpp xml_parser.cpp)

# srcFact application
add_executable(srcFacts ${SOURCE})

# Turn on warnings
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # standard warnings
    add_compile_options(-Wall)
endif()

# Extract the demo input srcML file
file(ARCHIVE_EXTRACT INPUT ${CMAKE_SOURCE_DIR}/demo.xml.zip)

# Demo run command
add_custom_target(run
        COMMENT "Run demo"
        COMMAND time ./srcFacts < demo.xml
        DEPENDS srcFacts
        USES_TERMINAL
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
