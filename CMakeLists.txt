cmake_minimum_required(VERSION 3.5.1)

################################################################################

project(gaia_test)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/dist/test)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(gaia_test ${CMAKE_SOURCE_DIR}/test/demo.cpp)
target_link_libraries(gaia_test gtest_main)
add_test(NAME gaia_test COMMAND gaia)

################################################################################