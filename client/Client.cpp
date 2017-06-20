//
// Created by kyxo on 6/19/17.
//

#include "Client.hpp"

namespace 		Client
{

  Client::Client() : _size(0, 0)
  {}

  Client::~Client()
  {}

  void Client::initTab()
  {
    _tab["msz"] = [&](const std::vector<std::string> &t) { _msz(t); };
    _tab["bct"] = [&](const std::vector<std::string> &t) { _bct(t); };
    _tab["tna"] = [&](const std::vector<std::string> &t) { _tna(t); };
    _tab["pnw"] = [&](const std::vector<std::string> &t) { _pnw(t); };
  }

  void Client::call(std::vector<std::string> const &t)
  {
    if (_tab.find(t[0]) != _tab.end())
      _tab[t[0]](t);
  }

  void Client::_msz(const std::vector<std::string> &t)
  {
    if (t.size() != 4)
      return;
    _size.setX(std::atoi(t[1].c_str()));
    _size.setY(std::atoi(t[2].c_str()));
  }

  void Client::_bct(const std::vector<std::string> &t)
  {
    if (t.size() != 11)
      return;
    _map[{std::atoi(t[1].c_str()), std::atoi(t[2].c_str())}].set_res(t);
  }

  void Client::_tna(const std::vector<std::string> &t)
  {
    if (t.size() != 3)
      return;
    _team.push_back(t[1]);
  }


  void Client::_pnw(std::vector<std::string> const &t)
  {
    if (t.size() != 8)
      return ;
    _player.push_back(Character(~t[1], {~t[2], ~t[3]}, (Character::DIR)~t[4], ~t[5], t[6]));
  }

  int operator~(std::string const &t)
  {
    return std::atoi(t.c_str());
  }

}