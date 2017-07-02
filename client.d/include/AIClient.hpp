//
// Created by vincent on 24/06/17.
//

#ifndef CLIENT_D_AICLIENT_HPP
#define CLIENT_D_AICLIENT_HPP

#include <utility>
#include <string>
#include <unordered_map>
#include <map>
#include <mendatory/client.h>
#include <vector>
#include <list>
#include "proxy.hpp"
#include "commun.h"
#include "Request.hpp"

using t_inventory = std::unordered_map<t_resource, size_t, std::hash<int>>;

namespace zappy
{
  class Proxy;

  class AIClient
  {
   public:

    static const std::unordered_map<t_resource, std::string, std::hash<int>>	RESOURCES_TO_STR;
    static const std::unordered_map<std::string, t_resource>			STR_TO_RESOURCES;
    static const std::unordered_map<t_resource, RequestType, std::hash<int>>	RESOURCE_TO_REQUEST;

    struct SIncantation {
      size_t 							nbOfPlayers;
      std::unordered_map<t_resource, size_t, std::hash<int>>	resources;
    };

    AIClient(const t_arg &args);
    ~AIClient();

    void  ProxyRegister(Proxy *prox, int x, int y);
    zappy::RequestType 						update(std::string input);

   private:

    static const std::vector<SIncantation>			INCANTATIONS;
    unsigned int						FOOD_MIN;

    unsigned int						_level;
    std::pair<size_t, size_t >					_worldDimension;
    t_arg							_args;
    size_t 							_incantationLevel;
    t_inventory							_currentInventory;
    std::vector<t_inventory>					_currentLook;
    bool 							_isInventoryData;
    std::string							_outputSave;
    size_t 							_broadcastCyle;

    void							_play();
    void 							_look();
    void                            _broadcast();
      void                          _broadcastAction(const std::string &str);
      void                          _messageAction(const std::string &str);
      std::string                   _my_decrypt(const std::string &str);
    void							_getInventory(const std::string &data);
    bool 							_isNeeded(const t_resource) const;
    void 							_go(const unsigned int tile_number, const t_resource);
    void                          _go(const unsigned int pos);
    std::list<RequestType>					_todo;
    std::list<RequestType>					_OutputType;
    std::vector<t_inventory>					_lookParse(const std::string &look);
    void                                            		_extractResources(const std::string &str,
										  t_inventory &inventory);
    void                                            		_initInventory(t_inventory &inventory);
    void 							_addTodo(const RequestType);
    void 							_lookAction(const std::string &);
    void 							_incantationAction(const std::string &);
    void 							_inventoryAction(const std::string &);
    void 							_randomDirection();
    std::size_t 						_howManyResourses(const t_resource resource, const int tile_number) const;
    int 							_moveCalculate(const int middle, const int tile_number);
    bool 							_readyFoIncantation();
    void 							_setObjectDown();
    void 							_takeUselessObject();

    Proxy                           				*_prox;
    bool 							_mode;
    std::map<zappy::RequestType, std::function<void(const std::string &)>>	_actions;
    std::map<int, std::function<void(void)>> _deplacement;
  };
}

#endif //CLIENT_D_AICLIENT_HPP
