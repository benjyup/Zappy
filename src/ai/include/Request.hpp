//
// Created by Jean-Adrien on 27/06/17.
//

#ifndef CLIENT_D_REQUEST_HPP
#define CLIENT_D_REQUEST_HPP

#include <functional>
#include <map>

namespace zappy {
  typedef enum {
    FORWARD = 0,
    RIGHT,
    LEFT,
    LOOK,
    BROADCAST,
    INCANTATION,
    INCANTATION_VOID,
    TAKE_FOOD,
    TAKE_LINEMATE,
    TAKE_DERAUMERE,
    TAKE_SIBUR,
    TAKE_MENDIANE,
    TAKE_PHIRAS,
    TAKE_THYSTAME,
    SET_FOOD,
    SET_LINEMATE,
    SET_DERAUMERE,
    SET_SIBUR,
    SET_MENDIANE,
    SET_PHIRAS,
    SET_THYSTAME,
    INVENTORY,
      FORK,
    NOOP
  } RequestType;

  class Request {
   public:
    Request(RequestType);
    ~Request();

      int execute(std::string &str);

   protected:
    std::map<zappy::RequestType, std::function<int(std::string&)>> _function_ptr;
    RequestType _type;
    void        *data;
  };
}

#endif //CLIENT_D_REQUEST_HPP
