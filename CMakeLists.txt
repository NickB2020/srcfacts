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
set(SOURCE srcFacts.cpp refillBuffer.cpp XMLParser.cpp xml_parser.cpp)

# srcFact application
add_executable(srcFacts ${SOURCE})

# Source files for xmlstats
set(XMLSTATS_SOURCE xmlstats.cpp XMLParser.cpp refillBuffer.cpp xml_parser.cpp)

# xmlstats application
add_executable(xmlstats ${XMLSTATS_SOURCE})

# Source files for identity
set(XMLSTATS_SOURCE identity.cpp XMLParser.cpp refillBuffer.cpp xml_parser.cpp)

# identity application
add_executable(identity ${XMLSTATS_SOURCE})

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

# xmlstats run command
add_custom_target(runxmlstats
        COMMENT "Run xmlstats"
        COMMAND time ./xmlstats < demo.xml
        DEPENDS xmlstats
        USES_TERMINAL
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# identity run command
add_custom_target(runidentity
        COMMENT "Run identity"
        COMMAND time ./identity < demo.xml > democopy.xml
        DEPENDS identity
        USES_TERMINAL
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
