# CMake minimum version
cmake_minimum_required(VERSION 2.4)

# project name and language
project(MZC4 CXX)

# Check <strsafe.h>
include(CheckIncludeFile)
check_include_file("strsafe.h" HAVE_STRSAFE_H)
if (NOT HAVE_STRSAFE_H)
    add_definitions(-DNO_STRSAFE)
endif()

# subdirectories
subdirs(samples)
