//
// Created by peixot_b on 20/06/17.
//

#include <Vector3d.hpp>
#include <ctime>
#include <iostream>
#include "Minerals.hpp"

Minerals::Minerals(Vector3d const &pos, TYPE type) : _pos(pos), _type(type)
{
  //Assign his texture
}

Minerals::Minerals(Vector3d const &pos) : _pos(pos) // Without type which will generate it's own type
{
  srand(static_cast <unsigned> (time(0)));
  (uint8_t)_type = genRandNbr(1, 6);
  //Assign his texture
}

Minerals::~Minerals()
{
  //Delete all the graphical ressources
}

const Vector3d	&Minerals::get_pos() const
{
  return _pos;
}

Minerals::TYPE	Minerals::get_type() const
{
  return _type;
}

void		Minerals::set_pos(const Vector3d &_pos)
{
  Minerals::_pos = _pos;
}

void		Minerals::set_type(Minerals::TYPE _type)
{
  Minerals::_type = _type;
}

uint8_t		Minerals::genRandNbr(uint8_t min, uint8_t max)
{
  uint8_t randNbr = min + static_cast <uint8_t > (rand()) / ( static_cast <uint8_t >(RAND_MAX / max));
  return (randNbr);
}