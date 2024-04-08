find_package(GTest CONFIG REQUIRED)

add_executable(Sim808.Tests)

target_include_directories(Sim808.Tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_sources(Sim808.Tests
    PRIVATE
        main.cpp
        # Short message service (SMS)
        Sim808/ShortMessages/Message.Test.cpp)

target_link_libraries(Sim808.Tests
    GTest::gtest
    Sim808::Core)
