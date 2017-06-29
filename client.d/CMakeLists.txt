
cmake_minimum_required(VERSION 3.4)

project(client_d)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

set(SOURCE_FILES main.cpp include/mendatory/client.h src/mendatory/argument.c src/mendatory/functionParse.c include/mendatory/argument.h src/mendatory/cookie.c include/mendatory/cookie.h include/mendatory/my_stack.h src/mendatory/my_stack.c include/mendatory/connection_manager.h src/mendatory/connection_manager.c src/mendatory/srv_write.c src/mendatory/srv_read.c src/zappy.cpp include/zappy.hpp include/ZappyException.hpp src/ZappyException.cpp include/server.hpp src/parser.cpp include/parser.hpp  src/AIClient.cpp include/AIClient.hpp include/proxy.hpp src/proxy.cpp include/Request.hpp src/Request.cpp)

include_directories(include ../include)


add_executable(zappy_ai ${SOURCE_FILES})
target_link_libraries(zappy_ai -pthread)
