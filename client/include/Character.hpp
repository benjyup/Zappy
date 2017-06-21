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
    DIR get_dir() const;

    void set_res(const std::vector<std::string> &_res);
    void set_pos(const Vector3d &_pos);
    void set_dir(DIR _dir);
    void set_level(int level);

    void	die();

   private:
    int 			_num;
    Vector3d			_pos;
    DIR 			_dir;
    int 			_level;
    std::string			_team;
    std::array<int, NBR_OF_RES>	_res;
    bool 			_alive;
   public:
    bool is_inc() const;

    void set_inc(bool _inc);

   private:
    bool 			_inc;
  };
};

#endif //PSU_2016_ZAPPY_CHARACTER_HPP