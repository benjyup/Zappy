//
// Created by peixot_b on 20/06/17.
//

#include <Vector3d.hpp>
#include <ctime>
#include <iostream>
#include "Ressource.hpp"

Ressource::Ressource(Vector3d const &pos, TYPE type, int nbrRessource) : _pos(pos), _type(type), _nbrRessource(nbrRessource)
{
  //Create node
  //Assign his texture
}

Ressource::Ressource(Vector3d const &pos) : _pos(pos) // Without type which will generate it's own type
{
  srand(static_cast <unsigned> (time(0)));
  _type = genRandType(Ressource::TYPE::FOOD, Ressource::TYPE::THYSTAME);
  //Create node
  //Assign his texture
}

Ressource::~Ressource()
{
  //Delete all the graphical ressources
}

const Vector3d	&Ressource::get_pos() const
{
  return _pos;
}

Ressource::TYPE	Ressource::get_type() const
{
  return _type;
}

int Ressource::get_nbrRessource() const
{
  return _nbrRessource;
}

void		Ressource::set_pos(const Vector3d &_pos)
{
  Ressource::_pos = _pos;
}

void		Ressource::set_type(Ressource::TYPE _type)
{
  Ressource::_type = _type;
}

void Ressource::set_nbrRessource(int nbrRessource)
{
  Ressource::_nbrRessource = nbrRessource;
}

Ressource::TYPE	Ressource::genRandType(TYPE min, TYPE max)
{
  TYPE randType = TYPE((int)min + rand() / (RAND_MAX / (int)max));
  return (randType);
}

void Ressource::gatherRessource(int nbrRessource)
{
  _nbrRessource -= nbrRessource;
}
