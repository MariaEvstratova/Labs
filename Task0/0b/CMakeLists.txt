cmake_minimum_required(VERSION 3.20)
project(word_count)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(CLANG_TIDY clang-tidy)

if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

add_executable(word_count
        main.cpp
        reader.cpp
        wordCounter.cpp
        writer.cpp
        reader.h
        wordCounter.h
        writer.h
)