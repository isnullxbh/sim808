find_package(GTest CONFIG REQUIRED)

add_executable(Sim808.CommandLineTool.Tests)

target_include_directories(Sim808.CommandLineTool.Tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_sources(Sim808.CommandLineTool.Tests
    PRIVATE
        main.cpp
        Sim808/CommandLineTool/Utility.Test.cpp)

target_link_libraries(Sim808.CommandLineTool.Tests
    GTest::gtest
    Sim808::CommandLineTool::Core)
