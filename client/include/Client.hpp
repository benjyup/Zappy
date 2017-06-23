//
// Created by kyxo on 6/19/17.
//

#ifndef ZAPPY_CLIENT_HPP
#define ZAPPY_CLIENT_HPP

#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <sstream>
#include <map>
#include <list>
#include "GraphicalLib.hpp"
#include "Character.hpp"
#include "irrlicht.h"
#include "Vector3d.hpp"
#include "Block.hpp"
#include "Eggs.hpp"

namespace 		Client
{
  int operator~(const std::string &t);
  class GraphicalLib;
  class Client
  {
   public:
    static const int SCALE = 15;
    Client();
    virtual ~Client();

    void initTab();
    void call(std::vector<std::string> const &);
    bool is_running() const;
    void	getTab(std::string const &s, std::vector<std::string> &tab);
    void	update();

   private:
    Vector3d 										_size;
    std::map<std::string, std::function<void(std::vector<std::string> const &)>>	_tab;
    std::map<Vector3d, Block> 								_map;
    std::vector<Character> 								_player;
    std::vector<std::string>								_team;
    std::vector<Eggs>								_Eggs;
    bool 									_running;
    int 									_sgtt;
    std::string									_winner;
    GraphicalLib								_lib;

    void _msz(std::vector<std::string> const &t);
    void _bct(std::vector<std::string> const &t);
    void _tna(std::vector<std::string> const &t);
    void _pnw(std::vector<std::string> const &t);
    void _ppo(std::vector<std::string> const &t);
    void _plv(std::vector<std::string> const &t);
    void _pin(std::vector<std::string> const &t);
    void _pex(std::vector<std::string> const &t);
    void _pbc(std::vector<std::string> const &t);
    void _pic(std::vector<std::string> const &t);
    void _pie(std::vector<std::string> const &t);
    void _pfk(std::vector<std::string> const &t);
    void _pdr(std::vector<std::string> const &t);
    void _pgt(std::vector<std::string> const &t);
    void _pdi(std::vector<std::string> const &t);
    void _enw(std::vector<std::string> const &t);
    void _eht(std::vector<std::string> const &t);
    void _ebo(std::vector<std::string> const &t);
    void _edi(std::vector<std::string> const &t);
    void _sgt(std::vector<std::string> const &t);
    void _seg(std::vector<std::string> const &t);
  };
};

#endif //ZAPPY_CLIENT_HPP
