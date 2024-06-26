# Distributed under the MIT License (See accompanying file /LICENSE )

# CMake build : global project

cmake_minimum_required (VERSION 3.3)

project (GUIDE ME)

add_executable(project main.cpp Graph.h City.h FileHandler.h Menu.h TransportationMethod.h Utilities.h)