//
// Created by kyxo on 6/20/17.
//

#ifndef PSU_2016_ZAPPY_CHARACTER_HPP
#define PSU_2016_ZAPPY_CHARACTER_HPP

#include <vector>
#include <array>
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
    int get_level() const;
    bool is_inc() const;
    bool is_lay() const;

    void set_inc(bool _inc);
    void set_res(const std::vector<std::string> &_res);
    void set_pos(const Vector3d &_pos);
    void set_dir(DIR _dir);
    void set_level(int level);
    void dec_res(int res);
    void inc_res(int res);
    void set_lay(bool _lay);

    void	die();

   private:
    int 			_num;
    Vector3d			_pos;
    DIR 			_dir;
    int 			_level;
    std::string			_team;
    std::array<int, Block::NBR_OF_RES>	_res;
    bool 			_alive;
    bool 			_inc;
    bool 			_lay;
  };
};

#endif //PSU_2016_ZAPPY_CHARACTER_HPP