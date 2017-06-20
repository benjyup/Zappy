//
// Created by kyxo on 6/19/17.
//

#include "Block.hpp"

namespace 		Client
{

  Block::Block()
  {}

  Block::~Block()
  {

  }

  const std::array<int, NBR_OF_RES> &Block::getRes() const
  {
    return _res;
  }

  void Block::set_res(const std::vector<std::string> &res)
  {
    int j = -3;
    for (auto const &i : res)
      {
	if (j > -1 && !i.empty())
	    _res[j] = std::atoi(i.c_str());
	j++;
      }
  }
}