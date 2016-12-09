cmake_minimum_required(VERSION 3.3)
project(Shepherd-Simulation)

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/build/)
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
set(CMAKE_BUILD_DIRECTORY ${dir})
set(CMAKE_BINARY_DIR  ${dir})
set(EXECUTABLE_OUTPUT_PATH ${dir})
set(LIBRARY_OUTPUT_PATH ${dir}lib)
set(CMAKE_CACHEFILE_DIR ${dir})

set(SOURCE
        main.cpp
        sailboat.cpp
        widgetsimu.cpp)


add_executable(simu ${SOURCE})
target_link_libraries(simu "-lSDLmain -lSDL -lGLU -lGL")