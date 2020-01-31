Project(AST)

cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 11)

include_directories(${gtest_SOURCE_DIR}/include/)

add_compile_options(
-Wall
-Wextra
-Werror
)

add_executable(
    unit_test
    test.cpp
    lexer.cpp
    parser.cpp
    interpreter.cpp)

target_link_libraries(
    unit_test
    gtest
)
