cmake_minimum_required(VERSION 3.7)
project(client_d)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

set(SOURCE_FILES main.cpp include/mendatory/client.h src/mendatory/argument.c src/mendatory/functionParse.c include/mendatory/argument.h src/mendatory/cookie.c include/mendatory/cookie.h)

include_directories(include)
add_executable(zappy_client ${SOURCE_FILES})