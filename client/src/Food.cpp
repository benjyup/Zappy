//
// Created by peixot_b on 20/06/17.
//

#include <Vector3d.hpp>
#include "Food.hpp"

Food::Food(Vector3d const &pos) : _pos(pos)
{
  _apple = 2;
  //Creation of the Apple tree at _pos
}

Food::~Food()
{

}

const Vector3d &Food::get_pos() const
{
  return _pos;
}

uint8_t Food::get_apple() const
{
  return _apple;
}

void Food::set_pos(const Vector3d &_pos)
{
  Food::_pos = _pos;
}

void Food::set_apple(uint8_t _apple)
{
  Food::_apple = _apple;
}

void Food::eat()
{
  _apple -= 1;
  // The character can live longer
  if (_apple == 0)
    {
      // No more food, Destruction of the Apple tree
    }
}
