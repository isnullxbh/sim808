add_executable(Sim808.CommandLineTool)

target_include_directories(Sim808.CommandLineTool
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_sources(Sim808.CommandLineTool
    PRIVATE
        main.cpp
        Sim808/CommandLineTool/CommandDispatcher.cpp)

target_link_libraries(Sim808.CommandLineTool
    PUBLIC
        Sim808::Core
        Sim808::CommandLineTool::Core)
