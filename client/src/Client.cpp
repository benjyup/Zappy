
//
// Created by kyxo on 6/19/17.
//

#include "Client.hpp"

namespace 		Client
{
  Client::Client() : _size(0, 0)
  {
    std::vector<std::string> tab;
    std::string			s;
    int 			i = 0;

    std::cout << "Graphic";
    while (i < 3)
      {
	std::cin >> s;
	tab.push_back(s);
	i++;
      }
    _msz(tab);
  }

  Client::~Client()
  {}

  void Client::initTab()
  {
    _tab["msz"] = [&](const std::vector<std::string> &t) { _msz(t); };
    _tab["bct"] = [&](const std::vector<std::string> &t) { _bct(t); };
    _tab["tna"] = [&](const std::vector<std::string> &t) { _tna(t); };
    _tab["pnw"] = [&](const std::vector<std::string> &t) { _pnw(t); };
    _tab["ppo"] = [&](const std::vector<std::string> &t) { _ppo(t); };
    _tab["plv"] = [&](const std::vector<std::string> &t) { _plv(t); };
    _tab["pin"] = [&](const std::vector<std::string> &t) { _pin(t); };
    _tab["pex"] = [&](const std::vector<std::string> &t) { _pex(t); };
    _tab["pbc"] = [&](const std::vector<std::string> &t) { _pbc(t); };
  }

  void Client::call(std::vector<std::string> const &t)
  {
    if (_tab.find(t[0]) != _tab.end())
      _tab[t[0]](t);
  }

  void Client::_msz(const std::vector<std::string> &t)
  {
    if (t.size() != 3)
      return;
    _size.setX(std::atoi(t[1].c_str()));
    _size.setY(std::atoi(t[2].c_str()));
  }

  void Client::_ppo(const std::vector<std::string> &t)
  {
//    std::cerr << "ppo Function" << t.size() << std::endl;
    if (t.size() != 5)
      return;
//    std::cerr << "Player Num" << t[1] << std::endl;
//    std::cerr << "X : " << ~t[2] << std::endl;
//    std::cerr << "Y : " << ~t[3] << std::endl;
//    std::cerr << "DIR : " << t[4] << std::endl;
    _player[~t[1] - 1].set_pos({~t[2], ~t[3]});
    _player[~t[1] - 1].set_dir((Character::DIR )~t[4]);
  }

  void Client::_bct(const std::vector<std::string> &t)
  {
    if (t.size() != 10)
      return;
    _map[{~t[1], ~t[2]}].set_res(t);
  }

  void Client::_tna(const std::vector<std::string> &t)
  {
    if (t.size() != 2)
      return;
    _team.push_back(t[1]);
  }

  void Client::_pnw(std::vector<std::string> const &t)
  {
    if (t.size() != 7)
      return ;
    std::cerr << "Pnw Function" << std::endl;
    _player.push_back(Character(~t[1], Vector3d(~t[2], ~t[3]), (Character::DIR)~t[4], ~t[5], t[6]));
    _map[{~t[2], ~t[3]}].add_player(~t[1]);
  }

  void Client::_plv(std::vector<std::string> const &t)
  {
    if (t.size() != 3)
      return ;
    std::cerr << "Plv Function" << std::endl;
    _player[~t[1] - 1].set_level(~t[2]);
  }

  void Client::_pin(std::vector<std::string> const &t)
  {
    if (t.size() != 11)
      return ;
    std::cerr << "Pin Function" << std::endl;
    _map[_player[~t[1] - 1].get_pos()].del_player(~t[1]);
    _map[{~t[2], ~t[3]}].add_player(~t[1]);
    _player[~t[1] - 1].set_pos({~t[2], ~t[3]});
    _player[~t[1] - 1].set_res(t);
  }

  void Client::_pex(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    _player[~t[1] - 1].die();
  }

  void Client::_pbc(std::vector<std::string> const &t)
  {
    if (t.size() <= 2)
      return ;
    //broadcasting
  }

  void Client::_pic(std::vector<std::string> const &t)
  {
    if (t.size() <= 5)
      return ;
    
  }

  int operator~(std::string const &t)
  {
    return std::atoi(t.c_str());
  }
}
