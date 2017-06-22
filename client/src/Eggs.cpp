//
// Created by peixot_b on 20/06/17.
//

#include <Vector3d.hpp>
#include "Eggs.hpp"

Eggs::Eggs(Vector3d const &pos, int father) : _pos(pos), _state(EGGSSTATE::close), _father(father)
{
  //Creation of the node
  //Setting of the texture
  //Positionning on the map
}

Eggs::~Eggs()
{
  //Destruction of the node
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
  //Generation of the eclosion animation
  // then a new character appear in the map
  _state = EGGSSTATE::hatch;
}

void Eggs::die()
{
  _state = EGGSSTATE::die;
}
