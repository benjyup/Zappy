//
// Created by Jean-Adrien on 27/06/17.
//

#ifndef CLIENT_D_PROXY_HPP
#define CLIENT_D_PROXY_HPP

#include "../src/AIClient.hpp"
#include "zappy.hpp"

namespace zappy
{
    class AIClient;

    typedef enum  {
        FORWARD,
        RIGHT,
        LEFT,
        LOOK,
        BROADCAST
    } RequestType;

    template <typename T>
    class Request
    {
    public:
        Request(RequestType);

        ~Request();

    protected:
        RequestType _type;
        T           _data;
    };

    class Proxy
    {
    public:
        Proxy(zappy::AIClient &, zappy::Zappy &);
        ~Proxy();

        void update();
    private:
        bool            _ready;
        AIClient        &_ia;
        zappy::Zappy    &_zap;
        int             _x;
        int             _y;
        int             _team;
    };
}

#endif //CLIENT_D_PROXY_HPP
