//
// Created by alice on 19/06/17.
//

#ifndef CLIENT_D_ZAPPY_HPP
#define CLIENT_D_ZAPPY_HPP

extern "C"
{
#include "mendatory/argument.h"
#include "mendatory/cookie.h"
};

namespace zappy {
    class Zappy {
    public:
        Zappy(int, char **);
        ~Zappy();

    private:
        t_arg       _arg;
        t_cookie    _cook;
    };
}

#endif //CLIENT_D_ZAPPY_HPP
