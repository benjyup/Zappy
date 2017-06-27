//
// Created by Jean-Adrien on 27/06/17.
//

#include "server.hpp"
#include "proxy.hpp"



zappy::Proxy::Proxy(zappy::AIClient &ia, zappy::Zappy &zap): _ia(ia), _ready(false), _zap(zap),
    _function_ptr({
                          {zappy::RequestType::FORWARD, [] () -> int {
                            srv_write("FORWARD\n");
                              return 0;
                          }},
                          {zappy::RequestType::LEFT, [] () -> int {
                              srv_write("LEFT\n");
                                return 0;
                          }},
                          {zappy::RequestType::RIGHT, [] () -> int {
                              srv_write("RIGHT\n");
                                return 0;
                          }}

                  })
{ }

zappy::Proxy::~Proxy() {}

void zappy::Proxy::update() {
    static int step = 0;
    char *s =   srv_read();
    std::string     input;
    input.clear();
    if (s)
        input = s;
    if (step == 0)
    {
        if (input.find("WELCOME") != std::string::npos)
        {
            std::cout << "welcome OK" << std::endl;
            step += 1;
            return;
        }
    }
    if (step == 1) {
        srv_write(_zap.getTeam());
        std::cout << "team name OK" << std::endl;
        step += 1;
        return;
    }
    if (step == 2)
    {
        if (!input.empty())
        {
            std::cout << input << std::endl;
            _team = std::stoul(input);
            std::cout << "team : " << _team<< std::endl;
            step += 1;
            return;
        }
    }
    if (step == 3)
    {
        if (!input.empty())
        {
            _x = std::stoul(input);
            _y = std::stoul(input.substr(input.find(' '), input.size() - 1));
            std::cout << "x : " << _x << std::endl << "y : " << _y << std::endl;
            step += 1;
            return;
        }
    }

}



template<typename T>
zappy::Request<T>::Request(RequestType type): _type(type) {

}

template<typename T>
zappy::Request<T>::~Request() {

}
