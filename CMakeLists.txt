cmake_minimum_required(VERSION 3.7)
project(PSU_2016_zappy)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        client/Client.cpp
        client/Client.hpp
        client/Vector3d.cpp
        client/Vector3d.hpp
        client/main.cpp
        include/ai.h
        include/commun.h
        include/server.h
        src/ai/main.c
        src/server/main.c client/Block.cpp client/Block.hpp)

add_executable(PSU_2016_zappy ${SOURCE_FILES})