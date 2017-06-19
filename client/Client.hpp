//
// Created by kyxo on 6/19/17.
//

#ifndef ZAPPY_CLIENT_HPP
#define ZAPPY_CLIENT_HPP

#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>
#include <bits/unordered_map.h>
#include "Vector3d.hpp"
#include "Block.hpp"
#include <map>

class Client
{
 public:
  Client();
  ~Client();
  void 			initTab();
  void			call(std::vector<std::string> const&);

 private:
  Vector3d									_size;
  std::map<std::string, std::function<void(std::vector<std::string> const &)>>	_tab;
  std::map<Vector3d, Block>							_map;

  void		_msz(std::vector<std::string> const &t);
  void		_bct(std::vector<std::string> const &t);
};


#endif //ZAPPY_CLIENT_HPP
