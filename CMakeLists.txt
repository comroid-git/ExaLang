cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(ExaLang)

cmake_policy(SET CMP0114 OLD)

set(ANTLR_VERSION 4.9.3)
set(ANTLR_EXECUTABLE $ENV{antlr_executable})
set(Java_JAVA_EXECUTABLE $ENV{JRE_HOME}/bin/java)

list(APPEND CMAKE_MODULE_PATH $ENV{antlr4_home}/cmake ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# compiler must be 11 or 14
set(CMAKE_CXX_STANDARD 11)

# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)
# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# add macros to generate ANTLR Cpp code from grammar
find_package(ANTLR REQUIRED)

# Call macro to add lexer and grammar to your build dependencies.
antlr_target(ExaLangLexer ExaLangLexer.g4 LEXER)
antlr_target(ExaLangParser ExaLangParser.g4 PARSER
        DEPENDS_ANTLR ExaLangLexer
        COMPILE_FLAGS -listener -visitor -lib ${ANTLR_ExaLangLexer_OUTPUT_DIR})

# include generated files in project environment
include_directories(${ANTLR_ExaLangLexer_OUTPUT_DIR})
include_directories(${ANTLR_ExaLangParser_OUTPUT_DIR})

# add generated grammar to demo binary target
add_executable(ExaLang src/ExaLang.cpp
        src/ExaLangRuntime.h src/ExaLangRuntime.cpp
        src/ExaStack.h src/ExaStack.cpp
        src/Value.h src/Value.cpp

        src/antlr/AbstractVisitor.h
        src/antlr/CodeVisitor.h src/antlr/CodeVisitor.cpp

        src/stmt/StatementBase.h
        src/stmt/StatementTestOp.h src/stmt/StatementTestOp.cpp

        ${ANTLR_ExaLangLexer_CXX_OUTPUTS}
        ${ANTLR_ExaLangParser_CXX_OUTPUTS})
target_link_libraries(ExaLang antlr4_static)
