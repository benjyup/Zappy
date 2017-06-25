
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
    srv_write("GRAPHIC");
    std::cerr << "Client created" << std::endl;
    std::string			s;

    while ((str = srv_read()) == NULL);
    s.assign(str);
    getTab(s, tab);
    _msz(tab);
    std::cerr << s;
    s.clear();
    while ((str = srv_read()) == NULL);
    s.assign(str);
    std::cerr << s;
    getTab(s, tab);
    _sgt(tab);
    this->_running = true;
    for (int x = 0; x < _size.getX(); x++)
      {
	for (int y = 0; y < _size.getY(); y++)
	  {
	    Vector3d v(x, y);
	    _map[y * _size.getX() + x] = Block(_lib.addNode(v, GraphicalLib::MESH::block, GraphicalLib::TEXT::grass, Client::SCALE, 0), v);
	    std::cerr << v << std::endl;
	    std::cerr << _map[v.getY() * _size.getX() + v.getX()].get_pos() << std::endl;
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
    if (t.size() != 5)
      return;
    Vector3d v = {~t[2], ~t[3]};
    int num = ~t[1] - 1;
    Vector3d playerPos = _player[num].get_pos();

    if (v != playerPos)
      {
	_map[playerPos.getX() + playerPos.getY() * _size.getX()].resetSpacePos(_lib.getPos(_player[num].get_id()));
	_player[num].set_idAnimation(_lib.addFlyStraightAnimator(_player[num].get_id(),
								 _lib.getPos(_player[num].get_id()), _map[v.getX() + v.getY() * _size.getX()].getSpacePos(), 1000, ~t[4]));
	_player[num].set_pos(v);
	_player[num].set_dir((Character::DIR) ~t[4]);
      }
  }

  void Client::_bct(const std::vector<std::string> &t)
  {
    int resLvl;

    if (t.size() != 10)
      return;
    Block &b = _map.at(~t[1] + _size.getX() * ~t[2]);
    resLvl = b.set_res(t);
    std::cerr << resLvl << std::endl;
    if (b.get_idRes() == 0 && resLvl > 0)
      b.set_idRes(_lib.addNode({~t[1], ~t[2]}, GraphicalLib::MESH::minerals, GraphicalLib::TEXT::none, (irr::f32)resLvl, 1));
    else if (resLvl == 0 && b.get_idRes() != 0)
	{
	  _lib.delNode(b.get_idRes());
	  b.set_idRes(0);
	}
      else if (_lib.getScale(b.get_idRes()).X != resLvl)
	  _lib.set_scale((irr::f32)resLvl, b.get_idRes());
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
    Vector3d v(~t[2], ~t[3]);
    std::cerr << "Pnw Function" << std::endl;
    _player.emplace_back(Character(~t[1], v,  (Character::DIR)~t[4], ~t[5], t[6],
				   _lib.addCharacterNode(_map[v.getX() + v.getY() * _size.getX()].getSpacePos(), GraphicalLib::TEXT::none, 0.7f, ~t[4])));
    _map[v.getX() + v.getY() * _size.getX()].add_player(~t[1]);
  }

  void Client::_plv(std::vector<std::string> const &t)
  {
    if (t.size() != 3)
      return ;
    int 	id;

    //set animation
    std::cerr << "Plv Function" << std::endl;
    _player[~t[1] - 1].set_level(~t[2]);
    id = _player[~t[1] - 1].get_id();
    _lib.set_scale(0.7f + (irr::f32)_player[~t[1] - 1].get_level() / 20, id);
  }

  void Client::_pin(std::vector<std::string> const &t)
  {
    if (t.size() != 11)
      return ;
    Vector3d v(_player[~t[1] - 1].get_pos());
    Vector3d v2(~t[2], ~t[3]);

    std::cerr << "Pin Function" << std::endl;
    _map[v.getX() + v.getY() * _size.getX()].del_player(~t[1]);
    _map[v2.getX() + v2.getY() * _size.getX()].add_player(~t[1]);
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
    Vector3d v(~t[1], ~t[2]);
    int j = 4;

    while (j < t.size())
      {
	if (_player[~t[j] - 1].get_level() == ~t[3])
	  {
	    _lib.incantating(_player[~t[j] - 1].get_id());
	    _player[~t[j] - 1].set_inc(true);
	  }
	j++;
      }
  }

  void Client::_pie(std::vector<std::string> const &t)
  {
    if (t.size() < 4)
      return ;
    Vector3d v(~t[1], ~t[2]);
    int j =  v.getX() + v.getY() * _size.getX();
    for (auto const &i : _map[j].get_play())
      {
	if (_player[i - 1].is_inc())
	  {
	    _player[i - 1].set_inc(false);
	    _lib.idle(_player[i - 1].get_id());
	  }
      }
  }

  void Client::_pfk(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    int num = ~t[1] - 1;
    _player[num].set_lay(true);
    _lib.laying(_player[num].get_id());
  }

  void Client::_pdr(std::vector<std::string> const &t)
  {
    if (t.size() != 3)
      return ;
    //throwing
//    Vector3d v(_player[~t[1] - 1].get_pos());
//
//    _player[~t[1] - 1].dec_res(~t[2]);
//    _map[v.getX() + v.getY() * _size.getX()].inc_res(~t[2]);
  }

  void Client::_pgt(std::vector<std::string> const &t)
  {
    if (t.size() != 3)
      return ;
    int 	num;

    num = ~t[1] - 1;
    Vector3d v(_player[num].get_pos());
//    _player[num].inc_res(~t[2]);
//    _map[v.getX() + v.getY() * _size.getX()].dec_res(~t[2]);
    _player[num].set_idAnimation(-1);
    _lib.taking(_player[num].get_id());
  }

  void Client::_pdi(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    int 	num;

    num = ~t[1] - 1;
    Vector3d v(_player[num].get_pos());
    _player[num].die();
    _map[v.getX() + v.getY() * _size.getX()].del_player(num + 1);
    _lib.dying(_player[num].get_id());
  }

  void Client::_enw(std::vector<std::string> const &t)
  {
    if (t.size() != 5)
      return ;
    int num = ~t[2] - 1;
    int id = _player[num].get_id();

    _lib.idle(id);
    _player[num].set_lay(false);
    int idEggs = _lib.addEggsNode(_lib.getPos(id));
    _Eggs.emplace_back(Eggs({~t[3], ~t[4]}, ~t[2], ~t[1], idEggs));
  }

  void Client::_eht(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    int 	num = ~t[1] - 1;

    _Eggs[num].eclosion();
    _lib.addRotateAnimation(_Eggs[num].get_id());
  }

  void Client::_ebo(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    _Eggs[~t[1] - 1].die();
  }

  void Client::_edi(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    _Eggs[~t[1] - 1].die();
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
    return _running && _lib.is_running();
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
    int j;

    for (auto &i : _player)
      {
	if (i.is_alive() == Character::STATE::DEAD && i.get_id() != 0)
	  {
	    _lib.delNode(i.get_id());
	    i.set_id(0);
	  }
	if (i.is_alive() == Character::STATE::DYING && _lib.isAnimationEnd2(i.get_id()))
	  i.set_alive(Character::STATE::DEAD);
	if ((j = i.get_idAnimation()) > 0 && _lib.isAnimationEnd(j) || (j == -1 && _lib.isAnimationEnd2(i.get_id())))
	  {
	    _lib.idle(i.get_id());
	    i.set_idAnimation(0);
	  }
      }
    _lib.update();

  }

  int operator~(std::string const &t)
  {
    return std::atoi(t.c_str());
  }
}