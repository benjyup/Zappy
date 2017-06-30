//
// Created by Jean-Adrien on 27/06/17.
//

#include "server.hpp"
#include "proxy.hpp"



zappy::Proxy::Proxy(zappy::AIClient &ia, zappy::Zappy &zap): _ia(ia), _ready(false), _zap(zap),
    _function_ptr({
                          {zappy::FORWARD, [] () -> int {
                            srv_write("Forward");
                              return 0;
                          }},
                          {zappy::LEFT, [] () -> int {
                              srv_write("Left");
                                return 0;
                          }},
                          {zappy::RIGHT, [] () -> int {
                              srv_write("Right");
                                return 0;
                          }},
                          {zappy::LOOK, [] () -> int {
                              srv_write("Look");
                              return 0;
                          }},
			  {zappy::TAKE_FOOD, [] () -> int {
			    srv_write("Take food");
			    return 0;
			  }},
			  {zappy::TAKE_LINEMATE, [] () -> int {
			    srv_write("Take linemate");
			    return 0;
			  }},
			  {zappy::TAKE_DERAUMERE, [] () -> int {
			    srv_write("Take deraumere");
			    return 0;
			  }},
			  {zappy::TAKE_SIBUR, [] () -> int {
			    srv_write("Take sibur");
			    return 0;
			  }},
			  {zappy::TAKE_MENDIANE, [] () -> int {
			    srv_write("Take mendiane");
			    return 0;
			  }},
			  {zappy::TAKE_PHIRAS, [] () -> int {
			    srv_write("Take phiras");
			    return 0;
			  }},
			  {zappy::TAKE_THYSTAME, [] () -> int {
			    srv_write("Take thystame");
			    return 0;
			  }},
			  {zappy::INVENTORY, [] () -> int {
			    srv_write("Inventory");
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

