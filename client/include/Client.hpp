//
// Created by kyxo on 6/19/17.
//

#ifndef ZAPPY_CLIENT_HPP
#define ZAPPY_CLIENT_HPP

#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <list>
#include "Vector3d.hpp"
#include "Block.hpp"
#include "Character.hpp"

namespace 		Client
{

  class Client
  {
   public:
    Client();
    virtual ~Client();

    void initTab();
    void call(std::vector<std::string> const &);

   private:
    Vector3d 										_size;
    std::map<std::string, std::function<void(std::vector<std::string> const &)>>	_tab;
    std::map<Vector3d, Block> 								_map;
    std::vector<Character> 								_player;
    std::vector<std::string>								_team;

    void _msz(std::vector<std::string> const &t);
    void _bct(std::vector<std::string> const &t);
    void _tna(std::vector<std::string> const &t);
    void _pnw(std::vector<std::string> const &t);
  };
  int operator~(const std::string &t);
};

#endif //ZAPPY_CLIENT_HPP
