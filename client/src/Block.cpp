//
// Created by kyxo on 6/19/17.
//

#include <iostream>
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
    int j = 0;
    auto k = res.begin();
    while (k != res.end() && j < 4)
      {
	k++;
	j++;
      }
    j = 0;
    while (k != res.end())
      {
	_res[j] = std::atoi(k->c_str());
	std::cerr << _res[j] << " ";
	j++;
	k++;
      }
  }

  void Block::add_player(int player)
  {
    _play.push_front(player);
  }

  void Block::del_player(int player)
  {
    for (auto &i : _play)
    _play.remove_if([player](int p) {
      return p == player;
    });
  }
}