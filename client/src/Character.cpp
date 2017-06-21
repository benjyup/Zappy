//
// Created by kyxo on 6/20/17.
//

#include <cstring>
#include "Character.hpp"

namespace 		Client
{

  Character::Character(int num, Vector3d const &pos,
		       Character::DIR dir, int level,
		       std::string const &team) : _num(num), _pos(pos), _dir(dir), _level(level), _team(team), _alive(true),
						  _inc(false)
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
	_alive = false;
  }

  bool Character::is_inc() const
  {
    return _inc;
  }

  void Character::set_inc(bool _inc)
  {
    Character::_inc = _inc;
  }

}