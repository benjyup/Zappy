//
// Created by vincent on 24/06/17.
//

#ifndef CLIENT_D_AICLIENT_HPP
#define CLIENT_D_AICLIENT_HPP

#include <utility>
#include <cstring>
#include <unordered_map>
#include <regex>
#include <mendatory/client.h>
#include "commun.h"

namespace zappy
{

  class AIClient
  {
   public:

    struct SIncantation {
      size_t 							nbOfPlayers;
      std::unordered_map<t_resource, size_t, std::hash<int>>	linemate;
    };

    AIClient(const t_arg &args);
    ~AIClient();

   private:

    static const 	std::vector<SIncantation>			INCANTATIONS;

    std::pair<size_t, size_t >	_worldDimension;
    size_t 			_clietnNum;
    t_arg			_args;

    void 			_getWorldInformation(const std::string &informations);
    void			_play();
  };
}


#endif //CLIENT_D_AICLIENT_HPP
