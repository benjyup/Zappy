//
// Created by kyxo on 6/19/17.
//

#ifndef PSU_2016_ZAPPY_BLOCK_HPP
#define PSU_2016_ZAPPY_BLOCK_HPP

#include <vector>
#include <string>
#include <array>

# define NBR_OF_RES	7

class Block
{
 public:
  Block();
  virtual ~Block();

  void set_res(const std::vector<std::string> &_res);
  const std::array<int, NBR_OF_RES> &getRes() const;

 private:
  std::array<int, NBR_OF_RES>	_res;
};


#endif //PSU_2016_ZAPPY_BLOCK_HPP
