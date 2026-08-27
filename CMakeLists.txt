cmake_minimum_required(VERSION 3.28.3)
project(Solar_System_Simulator VERSION 1.0
                               DESCRIPTION "StormHewn's first rayLib project"
                               LANGUAGES CXX)

add_executable(simulator
                "Source Files/Main.cpp")
target_include_directories(simulator PUBLIC "Project Headers")
target_include_directories(simulator PUBLIC "Raylib Source/include")
target_link_directories(simulator PUBLIC "Raylib Source/lib")