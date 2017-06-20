cmake_minimum_required(VERSION 3.5)
project(client_graph)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

set(SOURCE_FILES
        src/main.cpp
        src/Block.cpp
        src/Character.cpp
        src/Client.cpp
        src/Minerals.cpp
        src/Vector3d.cpp
        include/Block.hpp
        include/Character.hpp
        include/Client.hpp
        include/Minerals.hpp
        include/Vector3d.hpp)

include_directories(include)

add_executable(client_graph ${SOURCE_FILES})

target_link_libraries(client_graph)