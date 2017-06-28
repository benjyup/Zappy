//
// Created by Jean-Adrien on 27/06/17.
//

#ifndef CLIENT_D_PROXY_HPP
#define CLIENT_D_PROXY_HPP

#include <list>
#include "zappy.hpp"
#include "AIClient.hpp"
#include "Request.hpp"

namespace zappy
{
class AIClient;

    class Proxy
    {
    public:
        Proxy(zappy::AIClient &, zappy::Zappy &);
        ~Proxy();

        void update(zappy::RequestType order);
    private:
        std::map<zappy::RequestType, std::function<int()>> _function_ptr;
        Request<std::vector<int>>   request_queu;
        bool            _ready;
        zappy::AIClient &_ia;
        zappy::Zappy    &_zap;
        int             _x;
        int             _y;
        int             _team;
    };
}

#endif //CLIENT_D_PROXY_HPP
