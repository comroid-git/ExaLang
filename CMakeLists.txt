project(ExaLang)

# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# compiler must be 17
set(CMAKE_CXX_STANDARD 17)
set(Java_JAVA_EXECUTABLE $ENV{JDK_11}/bin/java)

# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)

# Specify the version of the antlr4 library needed for this project.
# By default the latest version of antlr4 will be used.  You can specify a
# specific, stable version by setting a repository tag value or a link
# to a zip file containing the libary source.
set(ANTLR4_TAG 4.11.1)
set(ANTLR4_ZIP_REPOSITORY https://github.com/antlr/antlr4/archive/refs/tags/4.11.1.zip)

# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# set variable pointing to the antlr tool that supports C++
# this is not required if the jar file can be found under PATH environment
set(ANTLR_EXECUTABLE /dev/antlr/antlr-4.11.1-complete.jar)
# add macros to generate ANTLR Cpp code from grammar
find_package(ANTLR REQUIRED)

# Call macro to add lexer and grammar to your build dependencies.
antlr_target(ExaLangLexer grammar/ExaLangLexer.g4 LEXER)
antlr_target(ExaLangParser grammar/ExaLangParser.g4 PARSER VISITOR
        DEPENDS_ANTLR ExaLangLexer
        COMPILE_FLAGS -lib ${ANTLR_ExaLangLexer_OUTPUT_DIR})

# include generated files in project environment
include_directories(${ANTLR_ExaLangLexer_OUTPUT_DIR})
include_directories(${ANTLR_ExaLangParser_OUTPUT_DIR})

# add generated grammar to demo binary target
add_executable(ExaLang
        src/main.cpp

        ${ANTLR_ExaLangLexer_CXX_OUTPUTS}
        ${ANTLR_ExaLangParser_CXX_OUTPUTS}

        src/ExaLang.cpp
        src/ExaLangRuntime.h src/ExaLangRuntime.cpp
        src/ExaStack.h src/ExaStack.cpp
        src/Value.h src/Value.cpp

        src/stmt/StatementBase.h
        src/stmt/StatementTestOp.h src/stmt/StatementTestOp.cpp

        src/antlr/AbstractVisitor.h
        src/antlr/CodeVisitor.h src/antlr/CodeVisitor.cpp
)
# add generated grammar to demo binary target
target_link_libraries(ExaLang antlr4_static)
