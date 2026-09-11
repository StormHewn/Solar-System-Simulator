cmake_minimum_required(VERSION 3.28.3)
project(Solar_System_Simulator VERSION 1.0
                               DESCRIPTION "StormHewn's first rayLib project"
                               LANGUAGES CXX)

add_executable(simulator
    "Source Files/Engine.cpp"
    "Source Files/Main.cpp"
    "Source Files/Planet Sprite.cpp"
    "Source Files/Planet.cpp"
    "Source Files/Playback Renderer.cpp"
    "Source Files/Sim History.cpp")
target_include_directories(simulator PUBLIC "Project Headers")
target_include_directories(simulator PUBLIC "Raylib Source/include")
target_link_libraries(simulator PUBLIC "/home/matt-knox/Documents/VS Code/Git/Solar-System-Simulator/Raylib Source/lib/libraylib.so")