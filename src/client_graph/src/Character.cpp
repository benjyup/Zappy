//
// Created by kyxo on 6/20/17.
//

#include <cstring>
#include "Character.hpp"

namespace 		Client
{

  Character::Character(int num, Vector3d const &pos,
		       Character::DIR dir, int level,
		       std::string const &team, int id) : _num(num), _pos(pos), _dir(dir), _level(level), _team(team), _alive(STATE::ALIVE),
							  _inc(false), _lay(false), _id(id), _idAnimation(0)
  {
    std::cerr << "character created, x = " << _pos.getX() << "  y = " << _pos.getY() << std::endl;
  }

  Character::Character() : _pos({0, 0})
  {

  }

  Character::~Character()
  {
  }

  int Character::get_num() const
  {
    return _num;
  }

  const Vector3d &Character::get_pos() const
  {
    return _pos;
  }

  void Character::set_pos(const Vector3d &_pos)
  {
    Character::_pos = _pos;
  }

  void Character::set_res(const std::vector<std::string> &res)
  {
    int j = 0;
    auto k = res.begin();
    while (k != res.end() && j < 4)
      {
	k++;
	j++;
      }
    j = 0;
    while (k != res.end())
      {
	_res[j] = std::atoi(k->c_str());
	j++;
	k++;
      }
  }

  Character::DIR Character::get_dir() const
  {
    return _dir;
  }

  void Character::set_dir(Character::DIR _dir)
  {
    Character::_dir = _dir;
  }

  void Character::set_level(int level)
  {
    _level = level;
  }

  void Character::die()
  {
    _alive = STATE::DYING;
  }

  bool Character::is_inc() const
  {
    return _inc;
  }

  void Character::set_inc(bool _inc)
  {
    Character::_inc = _inc;
  }

  int Character::get_level() const
  {
    return _level;
  }

  void Character::inc_res(int res)
  {
    _res[res]++;
  }

  void Character::dec_res(int res)
  {
    _res[res]--;
  }

  bool Character::is_lay() const
  {
    return _lay;
  }

  void Character::set_lay(bool _lay)
  {
    Character::_lay = _lay;
  }

  int Character::get_id() const
  {
    return _id;
  }

  void Character::set_id(int _id)
  {
    Character::_id = _id;
  }

  int Character::get_idAnimation() const
  {
    return _idAnimation;
  }

  void Character::set_idAnimation(int _idAnimation)
  {
    Character::_idAnimation = _idAnimation;
  }

  Character::STATE Character::is_alive() const
  {
    return _alive;
  }

  void Character::set_alive(Character::STATE _alive)
  {
    Character::_alive = _alive;
  }

}