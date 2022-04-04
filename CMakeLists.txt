cmake_minimum_required(VERSION 3.21)
project(ExaLang)

set(CMAKE_CXX_STANDARD 20)

add_executable(ExaLang main.cpp
        antlr_generated/ExaLangBaseListener.h antlr_generated/ExaLangBaseListener.cpp
        antlr_generated/ExaLangBaseVisitor.h antlr_generated/ExaLangBaseVisitor.cpp
        antlr_generated/ExaLangLexer.h antlr_generated/ExaLangLexer.cpp
        antlr_generated/ExaLangListener.h antlr_generated/ExaLangListener.cpp
        antlr_generated/ExaLangParser.h antlr_generated/ExaLangParser.cpp
        antlr_generated/ExaLangVisitor.h antlr_generated/ExaLangVisitor.cpp)
include_directories($ENV{antlr4_home}/runtime/src)
