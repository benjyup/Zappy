//
// Created by Jean-Adrien on 27/06/17.
//

#include "server.hpp"
#include "proxy.hpp"



zappy::Proxy::Proxy(zappy::AIClient &ia, zappy::Zappy &zap): _ia(ia), _ready(false), _zap(zap),
    _function_ptr({
                          {zappy::FORWARD, [] () -> int {
                            srv_write("forward\n");
                              return 0;
                          }},
                          {zappy::LEFT, [] () -> int {
                              srv_write("LEFT\n");
                                return 0;
                          }},
                          {zappy::RIGHT, [] () -> int {
                              srv_write("RIGHT\n");
                                return 0;
                          }},
                          {zappy::LOOK, [] () -> int {
                              srv_write("LOOK\n");
                              return 0;
                          }},
                          {zappy::NOOP, [] () -> int {
                              return 0;
                          }}
                  })
{ }

zappy::Proxy::~Proxy() {}

std::string zappy::Proxy::update(zappy::RequestType order) {
    static int step = 0;
    char *s =   srv_read();
    std::string     input;
    input.clear();
    if (s) {
        input = s;
    }
        if (step == 0)
    {
        if (input.find("welcome") != std::string::npos ||
                input.find("WELCOME") != std::string::npos)
        {
            std::cout << "welcome OK" << std::endl;
            step += 1;
            return input;
        }
    }
    if (step == 1) {
        srv_write(_zap.getTeam());
        std::cout << "team name OK" << std::endl;
        step += 1;
        return input;
    }
    if (step == 2)
    {
        if (!input.empty())
        {
            _team = std::stoul(input);
            std::cout << "team : " << _team<< std::endl;
            step += 1;
            return input;
        }
    }
    if (step == 3)
    {
        if (!input.empty())
        {
            _x = std::stoul(input.substr(input.find(' ')));
            _y = std::stoul(input.substr(input.find(' '), input.size() - 1));
            std::cout << "x : " << _x << std::endl << "y : " << _y << std::endl;
            step += 1;
            _ia.ProxyRegister(this, _x, _y);
            return input;
        }
    }
    if (step == 4)
    {
        _function_ptr[order]();
    }
    return input;
}

