cmake_minimum_required(VERSION 2.8)
project(Shepherd-Simulation)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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

#set(SOURCE_SERVER
#        serverToBuoys.cpp
#        serverToBuoys.h)

set(SOURCE
        main.cpp
        sailboat.cpp
        buoy.cpp
        world.cpp
        networktools.cpp
        ${SOURCE_SERVER})

set(SOURCE_SDL
	client.c)

add_executable(simu.out ${SOURCE})

add_executable(client.out ${SOURCE_SDL})
#target_link_libraries(simu.out "-lSDLmain -lSDL -lGLU -lGL")
