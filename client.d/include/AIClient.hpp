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
    void 							setInventory(const t_inventory &);
    void 							setLook(const std::vector<t_inventory> &);

   private:

    static const std::vector<SIncantation>			INCANTATIONS;

    unsigned int						_level;
    std::pair<size_t, size_t >					_worldDimension;
    t_arg							_args;
    size_t 							_incantationLevel;
    t_inventory							_currentInventory;
    std::vector<t_inventory>					_currentLook;
    bool 							_isInventoryData;

    void							_play();
    void 							_look();
    void                            _broadcast(const std::string &data);
      void                          _broadcastAction(const std::string &str);
      void                          _messageAction(const std::string &str);
      std::string                   _my_decrypt(const std::string &str);
    void							_getInventory(const std::string &data);
    bool 							_isNeeded(t_resource);
    void 							_go(const unsigned int tile_number, const t_resource);
    std::list<RequestType>					_todo;
    std::list<RequestType>					_OutputType;
    std::vector<t_inventory>					_lookParse(const std::string &look);
    void                                            		_extractResources(const std::string &str,
										  t_inventory &inventory);
    void                                            		_initInventory(std::unordered_map<t_resource, size_t,
	    std::hash<int>> &inventory);
    void 							_addTodo(const RequestType);
    void 							_lookAction(const std::string &);
    void 							_inventoryAction(const std::string &);

    Proxy                           				*_prox;
    bool 							_mode;
    std::map<zappy::RequestType, std::function<void(const std::string &)>>	_actions;
  };
}

#endif //CLIENT_D_AICLIENT_HPP
