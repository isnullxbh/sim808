add_library(Sim808)

set_target_properties(Sim808
    PROPERTIES
        OUTPUT_NAME "Sim808"
        PREFIX      "")

target_include_directories(Sim808
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_sources(Sim808
    PRIVATE
        Sim808/Sim808.cpp)
