//
// Created by vincent on 24/06/17.
//

#ifndef CLIENT_D_AICLIENT_HPP
#define CLIENT_D_AICLIENT_HPP

#include <utility>
#include <string>
#include <unordered_map>
#include <mendatory/client.h>
#include <vector>
#include "proxy.hpp"
#include "commun.h"
#include "Request.hpp"

namespace zappy
{
  class Proxy;

  class AIClient
  {
   public:

    static const 	std::unordered_map<t_resource, std::string, std::hash<int>>	RESOURCES_TO_STR;
    static const 	std::unordered_map<std::string, t_resource>	STR_TO_RESOURCES;

    struct SIncantation {
      size_t 							nbOfPlayers;
      std::unordered_map<t_resource, size_t, std::hash<int>>	resources;
    };

    AIClient(const t_arg &args);
    ~AIClient();

    void  ProxyRegister(Proxy *prox, int x, int y);
    zappy::RequestType updade();
   private:

    static const 	std::vector<SIncantation>		INCANTATIONS;

    unsigned int						_level;
    std::pair<size_t, size_t >					_worldDimension;
    size_t 							_clietnNum;
    t_arg							_args;
    size_t 							_incantationLevel;
    std::unordered_map<t_resource, size_t, std::hash<int>>	_inventory;
    std::vector<std::unordered_map<t_resource, size_t,
	    std::hash<int>>>					_currentLook;

    void 							_getWorldInformation(const std::string &informations);
    void							_play();
    void							_eat();
    void 							_look();
    void							_getInventory();
    void 							_makeInventory(const std::string &resources);
    bool 							_isNeeded(t_resource);
    void 							_go(unsigned int tile_number);

    Proxy                           				*_prox;
  };
}


#endif //CLIENT_D_AICLIENT_HPP
