//
// Created by peixot_b on 20/06/17.
//

#ifndef PSU_2016_ZAPPY_MINERALS_HPP
#define PSU_2016_ZAPPY_MINERALS_HPP

#include "Vector3d.hpp"

class Minerals
{
 public:
  enum class TYPE : unsigned int
  {
    LINEMATE = 1,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
  };

  Minerals(Vector3d const &pos, TYPE type);
  Minerals(Vector3d const &pos);
  virtual ~Minerals();

  const Vector3d 	&get_pos() const;
  TYPE 			get_type() const;

  void 			set_pos(const Vector3d &_pos);
  void 			set_type(TYPE _type);

  TYPE 			genRandType(TYPE min, TYPE max);

 private:
  Vector3d		_pos;
  TYPE 			_type;
};

#endif //PSU_2016_ZAPPY_MINERALS_HPP
