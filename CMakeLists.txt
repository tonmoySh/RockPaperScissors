cmake_minimum_required(VERSION 3.14)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

project(RockPaperScissors CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#standard include directory
include_directories(include)

#define compiler warnings
if(MSVC)
    set(COMPILER_WARNING_FLAGS /W4 /WX)
else()
    set(COMPILER_WARNING_FLAGS -Wall -Wextra -Wpedantic -Werror)
endif()

#main game executable
add_executable(rps_game
    src/main.cpp
    src/rock_paper_scissors.cpp
)
target_compile_options(rps_game PRIVATE ${COMPILER_WARNING_FLAGS})

#fetch GoogleTest dependency automatically
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

#test executable
enable_testing()
add_executable(test_runner
    test/test_main.cpp
    src/rock_paper_scissors.cpp
)

target_compile_options(test_runner PRIVATE ${COMPILER_WARNING_FLAGS})
target_link_libraries(test_runner PRIVATE gtest_main)