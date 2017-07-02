
//
// Created by kyxo on 6/19/17.
//

#include <irrlicht.h>
#include <Character.hpp>
#include <random>
#include <ZappyException.hpp>
#include "Client.hpp"
#include "server.hpp"

namespace 		Client
{

  const 	std::map<Ressource::TYPE , std::string>	Client::RESOURCES_TO_STR = {
	  {Ressource::TYPE::FOOD, "food"},
	  {Ressource::TYPE::LINEMATE, "linemate"},
	  {Ressource::TYPE::DERAUMERE, "deraumere"},
	  {Ressource::TYPE::SIBUR, "sibur"},
	  {Ressource::TYPE::MENDIANE, "mendiane"},
	  {Ressource::TYPE::PHIRAS, "phiras"},
	  {Ressource::TYPE::THYSTAME, "thystame"}
  };

  Client::Client(zappy::Zappy const &z) : _size(0, 0), _running(false), _z(z), _sgtt(100)
  {
    std::vector<std::string> tab;
    char 			*str;
    std::string			s;

    _z.update();
    while ((str = srv_read()) == NULL)
      _z.update();
    srv_write("GRAPHIC");
    _z.update();
    while ((str = srv_read()) == NULL)
      _z.update();
    s.assign(str);
    getTab(s, tab);
    _msz(tab);
    s.clear();
    this->_running = true;
    if (_size.getX() <= 3 || _size.getX() > 40 || _size.getY() <= 3 || _size.getY() > 40)
      throw zappy::Exception("Bad size map\n");
    for (int x = 0; x < _size.getX(); x++)
      for (int y = 0; y < _size.getY(); y++)
	{
	  Vector3d v(x, y);
	  _map[y * _size.getX() + x] = Block(_lib.addNode(v, GraphicalLib::MESH::block, GraphicalLib::TEXT::grass, Client::SCALE, 0), v);
	}
    _sound.setGameMusic();
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
    _lib.set_text2("\nMap generee de la taille : ", true);
    _lib.set_text2(t[1].c_str(), false);
    _lib.set_text2("x", false);
    _lib.set_text2(t[2].c_str(), false);
  }

  void Client::_ppo(const std::vector<std::string> &t)
  {
    if (t.size() != 5)
      return;
    Vector3d v = {~t[2], ~t[3]};
    int num = ~t[1];
    Vector3d playerPos = _player[num].get_pos();

    if (_player[num].is_alive() != Character::STATE::ALIVE)
      return ;
    if (v != playerPos)
      {
	_map[playerPos.getX() + playerPos.getY() * _size.getX()].resetSpacePos(_lib.getPos(_player[num].get_id()));
	_player[num].set_idAnimation(_lib.addFlyStraightAnimator(_player[num].get_id(),
								 _lib.getPos(_player[num].get_id()), _map[v.getX() + v.getY() * _size.getX()].getSpacePos(), 6000 / _sgtt, ~t[4]));
	_player[num].set_pos(v);
	_player[num].set_dir((Character::DIR) ~t[4]);
      }
  }

  GraphicalLib::TEXT	Client::genRandType(GraphicalLib::TEXT min, GraphicalLib::TEXT max)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist6((int)min,(int)max);

    GraphicalLib::TEXT randType = static_cast<GraphicalLib::TEXT>(dist6(gen));

    return (randType);
  }

  void Client::_bct(const std::vector<std::string> &t)
  {
    int resLvl;

    if (t.size() != 10)
      return;
    Block &b = _map.at(~t[1] + _size.getX() * ~t[2]);
    resLvl = b.set_res(t);
    Vector3d v(~t[1], ~t[2]);
    GraphicalLib::TEXT i = genRandType(GraphicalLib::TEXT::minerals1, GraphicalLib::TEXT::minerals3);

    if (b.get_idRes() == 0 && resLvl > 0)
      {
	b.set_idRock(_lib.addNode(v, GraphicalLib::MESH::rock, GraphicalLib::TEXT::rock, (irr::f32)resLvl, 1));
	b.set_idRes(_lib.addNode(v, GraphicalLib::MESH::minerals,
				 i,
				 (irr::f32)resLvl, 1));
	_lib.set_text2("\nUn Minerai vient d\'apparaitre en : ", true);
	_lib.set_text2(t[1].c_str(), false);
	_lib.set_text2(" ", false);
	_lib.set_text2(t[2].c_str(), false);
      }
    else if (resLvl == 0 && b.get_idRes() != 0)
	{
	  _lib.delNode(b.get_idRes());
	  _lib.delNode(b.get_idRock());
	  b.set_idRes(0);
	  b.set_idRock(0);
	}
      else if (_lib.getScale(b.get_idRes()).X != resLvl && b.get_idRes() != 0)
	  {
	    _lib.set_scale((irr::f32)resLvl, b.get_idRes());
	    _lib.set_scale((irr::f32)resLvl, b.get_idRock());
	  }
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
    int 	j = 0;
    Vector3d v(~t[2], ~t[3]);

    for (auto &i : _team)
      {
	if (!i.compare(t[6]))
	  break ;
	j++;
      }
    _player[~t[1]] = (Character(~t[1], v,  (Character::DIR)~t[4], ~t[5], t[6],
				_lib.addCharacterNode(_map[v.getX() + v.getY() * _size.getX()].getSpacePos(), j, 0.7f, ~t[4])));
    _map[v.getX() + v.getY() * _size.getX()].add_player(~t[1]);
    _lib.set_text2("\nUn nouveau joueur : ", true);
    _lib.set_text2(t[1].c_str(), false);
    _lib.set_text2(" apparait en ", false);
    _lib.set_text2(t[2].c_str(), false);
    _lib.set_text2(" ", false);
    _lib.set_text2(t[3].c_str(), false);
  }

  void Client::_plv(std::vector<std::string> const &t)
  {
    if (t.size() != 3)
      return ;
    int 	num = ~t[1];
    int 	id = _player[num].get_id();

    if (_player[num].is_alive() != Character::STATE::ALIVE)
      return ;
    _player[num].set_level(~t[2]);
    _lib.set_scale(0.7f + (irr::f32)_player[num].get_level() / 20, id);
    _player[num].set_idAnimation(-1);
    _lib.uping(id);
    _lib.set_text2("\nLe joueur : ", true);
    _lib.set_text2(t[1].c_str(), false);
    _lib.set_text2(" est niveau ", false);
    _lib.set_text2(t[2].c_str(), false);
    _sound.lvlUpSound();
  }

  void Client::_pin(std::vector<std::string> const &t)
  {
    if (t.size() != 11)
      return ;
    int 	num = ~t[1];
    Vector3d v(_player[num].get_pos());
    Vector3d v2(~t[2], ~t[3]);

    if (_player[num].is_alive() != Character::STATE::ALIVE)
      return ;
    _map[v.getX() + v.getY() * _size.getX()].del_player(num);
    _map[v2.getX() + v2.getY() * _size.getX()].add_player(num);
    _player[num].set_pos(v2);
    _player[num].set_res(t);
  }

  void Client::_pex(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    int num = ~t[1];

    if (_player[num].is_alive() != Character::STATE::ALIVE)
      return ;
    _player[num].set_idAnimation(-1);
    _lib.pushing(_player[num].get_id());
    _lib.set_text2("\nLe joueur : ", true);
    _lib.set_text2(t[1].c_str(), false);
    _lib.set_text2(" les joueurs de la case : ", false);
    _sound.ejectSound();
  }

  void Client::_pbc(std::vector<std::string> const &t)
  {
    if (t.size() <= 2)
      return ;
    //broadcasting
    _lib.set_text2("\nLe joueur : ", true);
    _lib.set_text2(t[1].c_str(), false);
    _lib.set_text2(" dit a tout le monde ", false);
    _lib.set_text2(t[2].c_str(), false);
  }

  void Client::_pic(std::vector<std::string> const &t)
  {
    if (t.size() < 5)
      return ;
    Vector3d v(~t[1], ~t[2]);

    _player[~t[4]].set_inc(true);
    _lib.incantating(_player[~t[4]].get_id());
    _lib.set_text2("\nLe joueur : ", true);
    _lib.set_text2(t[4].c_str(), false);
    _lib.set_text2(" lance une incantation ", false);
    _sound.ritualSound();
  }

  void Client::_pie(std::vector<std::string> const &t)
  {
    if (t.size() < 4)
      return ;
    Vector3d v(~t[1], ~t[2]);
    int j =  v.getX() + v.getY() * _size.getX();
    for (auto const &i : _map[j].get_play())
      {
	if (_player[i].is_inc())
	  {
	    _player[i].set_inc(false);
	    _lib.idle(_player[i].get_id());
	  }
      }
  }

  void Client::_pfk(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    int num = ~t[1];

    if (_player[num].is_alive() != Character::STATE::ALIVE)
      return ;
    _player[num].set_lay(true);
    _lib.laying(_player[num].get_id());
    _lib.set_text2("\nLe joueur : ", true);
    _lib.set_text2(t[1].c_str(), false);
    _lib.set_text2(" pond un oeuf! ", false);
  }

  void Client::_pdr(std::vector<std::string> const &t)
  {
    if (t.size() != 3)
      return ;
    int 	num;

    num = ~t[1];
    if (_player[num].is_alive() != Character::STATE::ALIVE)
      return ;
    Vector3d v(_player[num].get_pos());
    _player[num].set_idAnimation(-1);
    _lib.taking(_player[num].get_id());
    _lib.set_text2("\nLe joueur : ", true);
    _lib.set_text2(t[1].c_str(), false);
    _lib.set_text2(" jette une ressource ", false);
    _lib.set_text2(t[2].c_str(), false);
    _sound.eatSound();
  }

  void Client::_pgt(std::vector<std::string> const &t)
  {
    if (t.size() != 3)
      return ;
    int 	num;

    num = ~t[1];
    if (_player[num].is_alive() != Character::STATE::ALIVE)
      return ;
    Vector3d v(_player[num].get_pos());
    _player[num].set_idAnimation(-1);
    _lib.taking(_player[num].get_id());
    _lib.set_text2("\nLe joueur : ", true);
    _lib.set_text2(t[1].c_str(), false);
    _lib.set_text2(" ramasse une ressource ", false);
    _lib.set_text2(RESOURCES_TO_STR.at((Ressource::TYPE )~t[2]).c_str(), false);
  }

  void Client::_pdi(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    int 	num;

    num = ~t[1];
    if (_player[num].is_alive() != Character::STATE::ALIVE)
      return ;
    Vector3d v(_player[num].get_pos());
    _player[num].die();
    _map[v.getX() + v.getY() * _size.getX()].del_player(num);
    _lib.dying(_player[num].get_id());
    _lib.set_text2("\nLe joueur : ", true);
    _lib.set_text2(t[1].c_str(), false);
    _lib.set_text2(" est mort de faim...", false);
  }

  void Client::_enw(std::vector<std::string> const &t)
  {
    if (t.size() != 5)
      return ;
    int num = ~t[2];
    int id = _player[num].get_id();

    if (_player[num].is_alive() != Character::STATE::ALIVE)
      return ;
    _lib.idle(id);
    _player[num].set_lay(false);
    int idEggs = _lib.addEggsNode(_lib.getPos(id));
    _Eggs[~t[1]] = Eggs({~t[3], ~t[4]}, ~t[2], ~t[1], idEggs);
    _lib.set_text2("\nL\'oeuf ", true);
    _lib.set_text2(t[1].c_str(), false);
    _lib.set_text2(" est pondu en position ", false);
    _lib.set_text2(t[3].c_str(), false);
    _lib.set_text2(" ", false);
    _lib.set_text2(t[4].c_str(), false);
  }

  void Client::_eht(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    int 	num = ~t[1];

    _Eggs[num].eclosion();
    _lib.addRotateAnimation(_Eggs[num].get_id());
    _lib.set_text2("\nL\'oeuf ", true);
    _lib.set_text2(t[1].c_str(), false);
    _lib.set_text2(" a éclos! ", false);
  }

  void Client::_ebo(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    int 	num = ~t[1];

    _lib.delNode(_Eggs[num].get_id());
    _Eggs[num].set_id(0);
    _Eggs[num].die();
    _lib.set_text2("\nL\'oeuf ", true);
    _lib.set_text2(t[1].c_str(), false);
    _lib.set_text2(" donne naissance a un nouveau joueur!", false);
  }

  void Client::_edi(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    int 	num = ~t[1];

    _lib.delNode(_Eggs[num].get_id());
    _Eggs[num].set_id(0);
    _Eggs[num].die();
    _lib.set_text2("\nL\'oeuf ", true);
    _lib.set_text2(t[1].c_str(), false);
    _lib.set_text2(" est mort de faim...", false);
  }

  void Client::_sgt(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    _sgtt = ~t[1];
    _lib.set_text2("\nL\'unite de temps est de ", true);
    _lib.set_text2(t[1].c_str(), false);
  }

  void Client::_seg(std::vector<std::string> const &t)
  {
    if (t.size() != 2)
      return ;
    _running = false;
    _winner = t[1];
    _lib.set_text2("\nPartie terminee ! L'equipe gagnante est ", true);
    _lib.set_text2(t[1].c_str(), false);
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

    if (_z.update() == 1)
      _running = false;
    for (auto &i : _player)
      {
	if (i.second.is_alive() == Character::STATE::DEAD && i.second.get_id() != 0)
	  {
	    _lib.delNode(i.second.get_id());
	    i.second.set_id(0);
	  }
	if (i.second.is_alive() == Character::STATE::DYING && _lib.isAnimationEnd2(i.second.get_id()))
	  i.second.set_alive(Character::STATE::DEAD);
	if ((j = i.second.get_idAnimation()) > 0 && _lib.isAnimationEnd(j) || (j == -1 && _lib.isAnimationEnd2(i.second.get_id())))
	  {
	    _lib.idle(i.second.get_id());
	    i.second.set_idAnimation(0);
	  }
      }
    _lib.update();
  }

  int operator~(std::string const &t)
  {
    return std::atoi(t.c_str());
  }
}