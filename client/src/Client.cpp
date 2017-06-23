
//
// Created by kyxo on 6/19/17.
//

#include <irrlicht.h>
#include <Character.hpp>
#include "Client.hpp"
#include "server.hpp"

namespace 		Client
{
  Client::Client() : _size(0, 0), _running(false)
  {
    std::vector<std::string> tab;
    char 			*str;
   // srv_write("GRAPHIC");
    std::cerr << "Client created" << std::endl;
//    std::string			s;
//
//    while ((str = srv_read()) == NULL);
//    s.assign(str);
//    getTab(s, tab);
//    _msz(tab);
//    std::cerr << s;
//    s.clear();
//    while ((str = srv_read()) == NULL);
//    s.assign(str);
//    std::cerr << s;
//    getTab(s, tab);
//    _sgt(tab);
    this->_running = true;
    for (int x = 0; x < 10; x++)
      {
	for (int y = 0; y < 10; y++)
	  {
//	    _map[{x, y}] = Block(, {x, y});
	    _map.emplace(std::make_pair<Vector3d, Block>({x, y}, Block(_lib.addNode({x, y}, GraphicalLib::MESH::block, GraphicalLib::TEXT::grass), {x, y})));
//					Block());
//	    _map[{x, y}].getNode()->setMaterialTexture(0, text);

//	    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
//	    node->setMaterialTexture(0, text);
//	    _map.at({x, y}) = Block(_smgr->addOctreeSceneNode(cube->getMesh(0), 0 , 1), {x, y});
	  }
      }
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
    _tab["pic"] = [&](const std::vector<std::string> &t) { _pic(t); };
    _tab["pie"] = [&](const std::vector<std::string> &t) { _pie(t); };
    _tab["pfk"] = [&](const std::vector<std::string> &t) { _pfk(t); };
    _tab["pdr"] = [&](const std::vector<std::string> &t) { _pdr(t); };
    _tab["pgt"] = [&](const std::vector<std::string> &t) { _pgt(t); };
    _tab["pdi"] = [&](const std::vector<std::string> &t) { _pdi(t); };
    _tab["enw"] = [&](const std::vector<std::string> &t) { _enw(t); };
    _tab["eht"] = [&](const std::vector<std::string> &t) { _eht(t); };
    _tab["ebo"] = [&](const std::vector<std::string> &t) { _ebo(t); };
    _tab["edi"] = [&](const std::vector<std::string> &t) { _edi(t); };
    _tab["sgt"] = [&](const std::vector<std::string> &t) { _sgt(t); };
    _tab["seg"] = [&](const std::vector<std::string> &t) { _seg(t); };
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
    _map.at({~t[1], ~t[2]}).set_res(t);
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
    if (t.size() < 5)
      return ;
    int i = 4;

    while (i + 1 < t.size())
      _player[~t[i++] - 1].set_inc(true);
  }

  void Client::_pie(std::vector<std::string> const &t)
  {
    if (t.size() < 4 || !t[3].compare("0"))
      return ;
    for (auto const &i : _map[{~t[1], ~t[2]}].get_play())
      {
	_player[i - 1].set_inc(false);
	_player[i - 1].set_level(_player[i - 1].get_level() + 1);
      }
  }

  void Client::_pfk(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    _player[~t[1] - 1].set_lay(true);
  }

  void Client::_pdr(std::vector<std::string> const &t)
  {
    if (t.size() != 3)
      return ;
    //throwing
    _player[~t[1] - 1].dec_res(~t[2]);
    _map[_player[~t[1 - 1]].get_pos()].inc_res(~t[2]);
  }

  void Client::_pgt(std::vector<std::string> const &t)
  {
    if (t.size() != 3)
      return ;
    //throwing
    _player[~t[1] - 1].inc_res(~t[2]);
    _map[_player[~t[1 - 1]].get_pos()].dec_res(~t[2]);
  }

  void Client::_pdi(std::vector<std::string> const &t)
  {
    //starving
    if (t.size() != 2)
      return ;
    _player[~t[1] - 1].die();
    _map[_player[~t[1] - 1].get_pos()].del_player(~t[1]);
  }

  void Client::_enw(std::vector<std::string> const &t)
  {
    if (t.size() != 5)
      return ;
    _Eggs.push_back(Eggs({~t[3], ~t[4]}, ~t[2]));
    _player[~t[2]].set_lay(false);
  }

  void Client::_eht(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    _Eggs[~t[1]].eclosion();
  }

  void Client::_ebo(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    _Eggs[~t[1]].die();
  }

  void Client::_edi(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    _Eggs[~t[1]].die();
  }

  void Client::_sgt(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    _sgtt = ~t[1];
  }

  void Client::_seg(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    _running = false;
    _winner = t[1];
  }

  bool Client::is_running() const
  {
    return _running;
  }

  void	Client::getTab(std::string const &s, std::vector<std::string> &tab)
  {
    std::stringstream	ssin;

    ssin << s;
    tab.clear();
    while (ssin.good())
      {
	std::string word;
	ssin >> word;
	if (!word.empty())
	  tab.push_back(word);
      }
  }

  void Client::update()
  {
    _lib.update();
  }

  int operator~(std::string const &t)
  {
    return std::atoi(t.c_str());
  }
}