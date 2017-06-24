//
// Created by kyxo on 6/19/17.
//

#ifndef PSU_2016_ZAPPY_BLOCK_HPP
#define PSU_2016_ZAPPY_BLOCK_HPP

#include <iostream>
#include <vector>
#include <forward_list>
#include <array>
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

    const std::array<int, NBR_OF_RES> &getRes() const;
    void set_res(const std::vector<std::string> &_res);
    void set_id(int _id);
    const std::forward_list<int> &get_play() const;

    int get_id() const;
    void add_player(int);
    void del_player(int);
    void inc_res(int res);
    void dec_res(int res);
    void init_res();

   private:
    std::array<int, NBR_OF_RES> 	_res;
    std::forward_list<int>		_play;
    Vector3d				_pos;
    int 				_id;
  };
};

#endif //PSU_2016_ZAPPY_BLOCK_HPP
