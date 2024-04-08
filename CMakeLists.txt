cmake_minimum_required(VERSION 3.25)
project(sim808
        VERSION 0.0.0
        DESCRIPTION "Driver for SIM808 cellular module"
        HOMEPAGE_URL "https://github.com/isnullxbh/sim808")

option(SIM808_BUILD_TESTS "Generates a build target for unit tests" OFF)
option(SIM808_BUILD_CLT "Generates a build target for the command-line tool" OFF)

add_subdirectory(src)
add_subdirectory(tools)

if(SIM808_BUILD_TESTS)
    add_subdirectory(tests)
endif()
