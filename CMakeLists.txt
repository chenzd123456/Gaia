cmake_minimum_required(VERSION 3.5.1)

################################################################################

project(gaia_test)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

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
target_link_libraries(gaia_test gtest_main pthread)
add_test(NAME gaia_test COMMAND gaia)

################################################################################

project(gaia_react_thread_example)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 11)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)

add_executable(gaia_react_thread_example 
    ${CMAKE_SOURCE_DIR}/example/ReactThread/main.cpp)

target_link_libraries(gaia_react_thread_example pthread)

################################################################################