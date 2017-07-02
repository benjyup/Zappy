//
// Created by Jean-Adrien on 20/06/17.
//

#ifndef CLIENT_D_ZAPPYEXCEPTION_HPP
#define CLIENT_D_ZAPPYEXCEPTION_HPP

#include <exception>
#include <string>

namespace zappy
{
    class Exception : public std::exception
    {
    public:
        Exception(const std::string &msg = "") noexcept;
        virtual ~Exception() noexcept ;
        virtual const char *what() const noexcept ;

    private:
        std::string                 _msg;
    };
}

#endif //CLIENT_D_ZAPPYEXCEPTION_HPP
