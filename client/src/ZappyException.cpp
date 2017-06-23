//
// Created by alice on 20/06/17.
//

#include "ZappyException.hpp"

zappy::Exception::Exception(const std::string &msg) noexcept : _msg(msg)
{

}

zappy::Exception::~Exception() noexcept
{

}

const char *zappy::Exception::what() const noexcept
{
    return (_msg.c_str());
}
