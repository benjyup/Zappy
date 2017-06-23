//
// Created by kyxo on 6/19/17.
//

#include "Block.hpp"
#include "Client.hpp"

namespace 		Client
{
  Block::Block(int id, Vector3d const &pos) : _pos(pos), _id(id)
  {
    init_res();
  }

  Block::Block() : _pos({0, 0})
  {
    std::cerr << "gros fdp" << std::endl;
  }

  Block::~Block()
  {

  }

  const std::array<int, 7> &Block::getRes() const
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
    _play.remove_if([player](int p) {
      return p == player;
    });
  }

  const std::forward_list<int> &Block::get_play() const
  {
    return _play;
  }

  void Block::inc_res(int res)
  {
    _res[res]++;
  }

  void Block::dec_res(int res)
  {
    _res[res]--;
  }

  void Block::init_res()
  {
    for (int i = 0; i < NBR_OF_RES; i++)
      _res[i] = 0;
  }

  int Block::get_id() const
  {
    return _id;
  }

  void Block::set_id(int _id)
  {
    Block::_id = _id;
  }
}