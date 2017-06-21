//
// Created by kyxo on 6/19/17.
//

#ifndef PSU_2016_ZAPPY_BLOCK_HPP
#define PSU_2016_ZAPPY_BLOCK_HPP

#include <vector>
#include <string>
#include <array>
#include <forward_list>

# define NBR_OF_RES	7

namespace 	Client
{
  class Block
  {
   public:
    Block();
    virtual ~Block();

    const std::array<int, NBR_OF_RES> &getRes() const;
    void set_res(const std::vector<std::string> &_res);
    void add_player(int);
    void del_player(int);

   private:
    std::array<int, NBR_OF_RES> _res;
    std::forward_list<int>		_play;
  };
};


#endif //PSU_2016_ZAPPY_BLOCK_HPP
