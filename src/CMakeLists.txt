find_package(PkgConfig REQUIRED)
pkg_check_modules(ASIO REQUIRED asio)

add_library(Sim808)
add_library(Sim808::Core ALIAS Sim808)

set_target_properties(Sim808
    PROPERTIES
        OUTPUT_NAME "Sim808"
        PREFIX      "")

target_include_directories(Sim808
    PUBLIC
        ${ASIO_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_sources(Sim808
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include
            FILES
                # Short message service (SMS)
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Sim808/ShortMessages/Message.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Sim808/ShortMessages/MessageStorageType.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Sim808/ShortMessages/MessageTransferType.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Sim808/ShortMessages/Service.hpp
                # SIM
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Sim808/CommandGateway.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Sim808/DefaultCommandGateway.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Sim808/ResultCode.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/../include/Sim808/Sim808.hpp)

target_sources(Sim808
    PRIVATE
        # Short message service (SMS)
        Sim808/ShortMessages/Message.cpp
        Sim808/ShortMessages/MessageStorageType.cpp
        Sim808/ShortMessages/Service.cpp
        # Utility
        Sim808/Utility/StringUtility.cpp
        # SIM
        Sim808/DefaultCommandGateway.cpp
        Sim808/ResultCode.cpp
        Sim808/Sim808.cpp)
