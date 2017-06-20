//
// Created by kyxo on 6/20/17.
//

#include "Character.hpp"

namespace 		Client
{

  Character::Character(int num, Vector3d const &pos,
		       Character::DIR dir, int level,
		       std::string const &team) : _num(num), _pos(pos), _dir(dir), _level(level), _team(team)
  {
  }

  Character::~Character()
  {
  }

  int Character::get_num() const
  {
    return _num;
  }

  void Character::set_num(int _num)
  {
    Character::_num = _num;
  }

  const Vector3d &Character::get_pos() const
  {
    return _pos;
  }

  void Character::set_pos(const Vector3d &_pos)
  {
    Character::_pos = _pos;
  }

  void Character::set_res(const std::string *res)
  {
    int 	j = 0;

    while (res)
      {
	_res[j] = atoi(res->c_str());
	res++;
      }
//    int j = -3;
//    for (auto const &i : res)
//      {
//	if (j > -1 && !i.empty())
//	    _res[j] = std::atoi(i.c_str());
//	j++;
//      }
  }

}