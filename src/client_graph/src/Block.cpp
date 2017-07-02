//
// Created by kyxo on 6/19/17.
//

#include "Block.hpp"
#include "Client.hpp"

namespace 		Client
{
  Block::Block(int id, Vector3d const &pos) : _pos(pos), _id(id), _idRes(0), _resLevel(0)
  {
    init_res();
    irr::f32 	j = Client::SCALE / 3;
    irr::f32 	k = Client::SCALE / 3;

    for (auto &i : _posAvailable)
      {
	i.first = {_pos.getX() * Client::SCALE - j + Client::SCALE / 3 / 2, Client::SCALE, _pos.getY() * Client::SCALE + k - Client::SCALE / 3 / 2};
	if (k < Client::SCALE)
	  k += Client::SCALE / 3;
	else
	  {
	    k = Client::SCALE / 3;
	    j += Client::SCALE / 3;
	  }
	i.second = false;
      }
  }

  Block::Block() : _pos({0, 0})
  {

  }

  Block::~Block()
  {

  }

  int Block::set_res(const std::vector<std::string> &res)
  {
    int j = 0;
    auto k = res.begin();
    while (k != res.end() && j < 3)
      {
	k++;
	j++;
      }
    j = 0;
    while (k != res.end())
      {
	_res[j++] = std::atoi(k->c_str());
	k++;
      }
    if ((j = get_sum()) == 0)
      _resLevel = 0;
    else if (j < 4)
	_resLevel = 1;
      else if (j < 8)
	  _resLevel = 2;
	else
	  _resLevel = 3;
    return _resLevel;
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

  void Block::init_res()
  {
    for (int i = 0; i < NBR_OF_RES; i++)
      _res[i] = 0;
  }

  int Block::get_id() const
  {
    return _id;
  }

  int Block::get_sum() const
  {
    int sum = 0;
    int j = 1;
    while (j < NBR_OF_RES)
      sum += _res[j++];
    return sum;
  }

  int Block::get_idRes() const
  {
    return _idRes;
  }

  void Block::set_idRes(int _idRes)
  {
    Block::_idRes = _idRes;
  }

  irr::core::vector3df const &Block::getSpacePos()
  {
    for (auto &i : _posAvailable)
      if (!i.second)
	{
	  i.second = true;
	  return i.first;
	}
    return _posAvailable.front().first;
  }

  const Vector3d &Block::get_pos() const
  {
    return _pos;
  }

  void Block::resetSpacePos(irr::core::vector3df const &pos)
  {
    for (auto &i : _posAvailable)
      {
	if (i.first == pos)
	  {
	    i.second = false;
	    break ;
	  }
      }
  }

  int Block::get_idRock() const
  {
    return _idRock;
  }

  void Block::set_idRock(int _idRock)
  {
    Block::_idRock = _idRock;
  }
}