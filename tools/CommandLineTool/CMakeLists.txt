add_subdirectory(libs)
add_subdirectory(src)

if(SIM808_BUILD_TESTS)
    add_subdirectory(tests)
endif()
