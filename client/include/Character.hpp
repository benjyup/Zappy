//
// Created by kyxo on 6/20/17.
//

#ifndef PSU_2016_ZAPPY_CHARACTER_HPP
#define PSU_2016_ZAPPY_CHARACTER_HPP

#include <iostream>
#include "Vector3d.hpp"
#include "Block.hpp"

namespace 		Client
{
  class Character
  {
   public:
    enum class DIR : uint8_t
    {
      NORTH = 1,
      EAST,
      SOUTH,
      OUEST
    };

    Character(int num, Vector3d const &pos, DIR, int level, std::string const &team);
    virtual ~Character();

    int get_num() const;
    const Vector3d &get_pos() const;

    void set_num(int _num);
    void set_res(const std::string *_res);
    void set_pos(const Vector3d &_pos);

   private:
    int 			_num;
    Vector3d			_pos;
    DIR 			_dir;
    int 			_level;
    std::string			_team;
    std::array<int, NBR_OF_RES>	_res;
  };
};

#endif //PSU_2016_ZAPPY_CHARACTER_HPP