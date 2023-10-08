# CMake minimum version
cmake_minimum_required(VERSION 3.0)

# project name and languages
project(MZC4 C CXX RC)

# Check <strsafe.h>
include(CheckIncludeFile)
check_include_file("strsafe.h" HAVE_STRSAFE_H)
if (NOT HAVE_STRSAFE_H)
    add_definitions(-DNO_STRSAFE)
endif()

# subdirectories
subdirs(samples)
