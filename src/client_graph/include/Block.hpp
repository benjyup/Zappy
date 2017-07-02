//
// Created by kyxo on 6/19/17.
//

#ifndef PSU_2016_ZAPPY_BLOCK_HPP
#define PSU_2016_ZAPPY_BLOCK_HPP

#include <iostream>
#include <vector>
#include <forward_list>
#include <array>
#include <vector3d.h>
#include "Vector3d.hpp"

namespace 	Client
{
  class Block
  {
   public:
    static const int NBR_OF_RES = 7;
    Block(int id, Vector3d const &);
    Block();
    virtual ~Block();

    int set_res(const std::vector<std::string> &_res);
    void set_idRes(int _idRes);
    void add_player(int);
    void del_player(int);
    void resetSpacePos(irr::core::vector3df const &);
    void set_idRock(int _idRock);

    int get_idRock() const;
    irr::core::vector3df const &getSpacePos();
    const std::forward_list<int> &get_play() const;
    int get_idRes() const;
    int get_id() const;
    int get_sum() const;
    const Vector3d &get_pos() const;

    void init_res();

   private:
    std::array<int, NBR_OF_RES> 	_res;
    std::forward_list<int>		_play;
    Vector3d				_pos;
    int 				_id;
    int 				_idRes;
    int 				_idRock;
    char 				_resLevel;
    std::array<std::pair<irr::core::vector3df, bool>, 9>	_posAvailable;
  };
};

#endif //PSU_2016_ZAPPY_BLOCK_HPP
