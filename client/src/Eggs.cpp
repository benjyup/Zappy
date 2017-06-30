//
// Created by peixot_b on 20/06/17.
//

#include <Vector3d.hpp>
#include "Eggs.hpp"

Eggs::Eggs(Vector3d const &pos, int father, int num, int id) :
	_pos(pos), _state(EGGSSTATE::close), _father(father), _num(num), _id(id)
{
}

Eggs::~Eggs()
{
}

const Vector3d &Eggs::get_pos() const
{
  return _pos;
}

void Eggs::set_pos(const Vector3d &_pos)
{
  Eggs::_pos = _pos;
}

void Eggs::eclosion()
{
  _state = EGGSSTATE::hatch;
}

void Eggs::die()
{
  _state = EGGSSTATE::die;
}

int Eggs::get_id() const
{
  return _id;
}

void Eggs::set_id(int _id)
{
  Eggs::_id = _id;
}

Eggs::Eggs() : _pos({0, 0})
{}
