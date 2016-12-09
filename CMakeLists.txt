cmake_minimum_required(VERSION 3.3)
project(Shepherd-Simulation)

set(SOURCE
        main.cpp
        sailboat.cpp
        widgetsimu.cpp)


add_executable(simu ${SOURCE})
target_link_libraries(simu "-lSDLmain -lSDL -lGLU -lGL")