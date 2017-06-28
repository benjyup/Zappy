//
// Created by alice on 27/06/17.
//

#include "Request.hpp"

template<typename T>
zappy::Request<T>::Request(zappy::RequestType type): _type(type) {

}

template<typename T>
zappy::Request<T>::~Request() {

}