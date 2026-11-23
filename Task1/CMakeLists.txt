cmake_minimum_required(VERSION 3.20)
project(trie)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(CLANG_TIDY clang-tidy)

if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

add_executable(trie
        main.cpp
        Trie.cpp
        Trie.h
)

include(FetchContent)
FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(trie_tests tests.cpp Trie.cpp)
target_link_libraries(trie_tests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(trie_tests)