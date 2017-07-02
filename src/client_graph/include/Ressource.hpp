//
// Created by peixot_b on 20/06/17.
//

#ifndef PSU_2016_ZAPPY_RESSOURCE_HPP
#define PSU_2016_ZAPPY_RESSOURCE_HPP

#include "Vector3d.hpp"

class Ressource
{
 public:
  enum class TYPE : unsigned int
  {
    FOOD = 0,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
  };

  Ressource(Vector3d const &pos, TYPE type, int nbrRessource);

  Ressource(Vector3d const &pos);

  virtual ~Ressource();

  const Vector3d &get_pos() const;

  TYPE get_type() const;

  void set_pos(const Vector3d &_pos);

  void set_type(TYPE _type);

  TYPE genRandType(TYPE min, TYPE max);

  int get_nbrRessource() const;

  void set_nbrRessource(int nbrRessource);

  void gatherRessource(int nbrRessource);


 private:
  Vector3d _pos;
  TYPE _type;
  int _nbrRessource;
};

#endif //PSU_2016_ZAPPY_RESSOURCE_HPP
