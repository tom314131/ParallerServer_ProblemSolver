cmake_minimum_required(VERSION 3.13)

project(ap_secondMS)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

file(GLOB algorithms "Algorithms/*.h" "Algorithms/*.cpp")
file(GLOB serverClient "Server Client/*.h" "Server Client/*.cpp")
file(GLOB solverCacher "Solver And Cacher/*.h" "Solver And Cacher/*.cpp")
file(GLOB etc "Etc/*.h" "Etc/*.cpp")
file(GLOB rootLayer "main.cpp")

add_executable(ap_secondMS ${etc} ${algorithms} ${serverClient} ${rootLayer}
        ${solverCacher} Drafts/client.h "Server Client/TCP_socket.cpp")