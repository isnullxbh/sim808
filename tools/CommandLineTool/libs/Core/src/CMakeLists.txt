add_library(Sim808.CommandLineTool.Core)
add_library(Sim808::CommandLineTool::Core ALIAS Sim808.CommandLineTool.Core)

set_target_properties(Sim808.CommandLineTool.Core
    PROPERTIES
        OUTPUT_NAME "Sim808.CommandLineTool.Core"
        PREFIX      "")

target_include_directories(Sim808.CommandLineTool.Core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_sources(Sim808.CommandLineTool.Core
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include
            FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Sim808/CommandLineTool/Utility.hpp)

target_sources(Sim808.CommandLineTool.Core
    PRIVATE
        Sim808/CommandLineTool/Utility.cpp)
