cmake_minimum_required(VERSION 3.5)
project(client_graph)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

set(SOURCE_FILES
        src/main.cpp
        src/Block.cpp
        src/Character.cpp
        src/Client.cpp
        src/Ressource.cpp
        src/Vector3d.cpp
        src/Eggs.cpp
        src/Drone.cpp
        src/parser.cpp
        src/zappy.cpp
        src/ZappyException.cpp
        src/mendatory/argument.c
        src/mendatory/connection_manager.c
        src/mendatory/cookie.c
        src/mendatory/functionParse.c
        src/mendatory/my_stack.c
        src/mendatory/srv_read.c
        src/mendatory/srv_write.c
        include/Block.hpp
        include/parser.hpp
        include/server.hpp
        include/zappy.hpp
        include/ZappyException.hpp
        include/Character.hpp
        include/Client.hpp
        include/Ressource.hpp
        include/Vector3d.hpp
        include/Eggs.hpp
        include/Drone.hpp
        src/GraphicalLib.cpp
        include/GraphicalLib.hpp
        src/Sound.cpp
        include/Sound.hpp)

include_directories(irrlicht-1.8.4/include src/ include/ include/mendatory ./irrKlang-64bit-1.5.0/include)

link_directories(./irrlicht-1.8.4/lib/Linux ./irrlicht-1.8.4/lib/Linux/deepinx86_64
        ./irrlicht-1.8.4/lib/Linux/useful ./irrKlang-64bit-1.5.0/bin/linux-gcc-64/)

add_executable(client_graph ${SOURCE_FILES})

target_link_libraries(client_graph Irrlicht.a GL.so libXxf86vm.so libIrrKlang.so libXext.so libX11.so libXcursor.so -lpthread)