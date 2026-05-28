cmake_minimum_required(VERSION 3.20)
project(mini_compiler LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_program(LLVM_CONFIG llvm-config REQUIRED)

execute_process(COMMAND ${LLVM_CONFIG} --version OUTPUT_VARIABLE LLVM_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --includedir OUTPUT_VARIABLE LLVM_INCLUDE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --cxxflags OUTPUT_VARIABLE LLVM_CXXFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --ldflags OUTPUT_VARIABLE LLVM_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${LLVM_CONFIG} --system-libs OUTPUT_VARIABLE LLVM_SYSTEM_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(
    COMMAND ${LLVM_CONFIG} --libs core support analysis codegen mc target scalaropts passes native nativecodegen asmparser asmprinter
    OUTPUT_VARIABLE LLVM_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "Found LLVM ${LLVM_VERSION}")

include_directories(${LLVM_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

BISON_TARGET(MiniParser
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.y
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp);

FLEX_TARGET(MiniLexer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.l
    ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

ADD_FLEX_BISON_DEPENDENCY(MiniLexer MiniParser)

set(SOURCES
    src/ast.cpp
    src/sema.cpp
    src/codegen.cpp
    src/object_emitter.cpp
    src/driver.cpp
    ${BISON_MiniParser_OUTPUTS}
    ${FLEX_MiniLexer_OUTPUTS})

add_executable(mini_cc ${SOURCES})
target_include_directories(mini_cc PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
separate_arguments(LLVM_CXXFLAGS NATIVE_COMMAND ${LLVM_CXXFLAGS})
separate_arguments(LLVM_LDFLAGS NATIVE_COMMAND ${LLVM_LDFLAGS})
separate_arguments(LLVM_LIBS NATIVE_COMMAND ${LLVM_LIBS})
separate_arguments(LLVM_SYSTEM_LIBS NATIVE_COMMAND ${LLVM_SYSTEM_LIBS})

target_compile_options(mini_cc PRIVATE ${LLVM_CXXFLAGS})
target_link_options(mini_cc PRIVATE ${LLVM_LDFLAGS})
target_link_libraries(mini_cc PRIVATE ${LLVM_LIBS} ${LLVM_SYSTEM_LIBS})
