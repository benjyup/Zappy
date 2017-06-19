//
// Created by kyxo on 6/19/17.
//

#include "Client.hpp"

Client::Client() : _size(0, 0)
{}

Client::~Client()
{}

void Client::_msz(const std::vector<std::string> &t)
{
  std::cerr << "msz" << t.size() <<std::endl;
  if (t.size() != 4)
    return ;
  std::cerr << "msz work" <<std::endl;
  _size.setX(std::atoi(t[1].c_str()));
  _size.setY(std::atoi(t[2].c_str()));
}

void Client::_bct(const std::vector<std::string> &t)
{
  std::cerr << "bct" << t.size() <<std::endl;
  if (t.size() != 11)
    return ;
  std::cerr << "x : " << std::atoi(t[1].c_str()) << " y : " << std::atoi(t[2].c_str()) << std::endl;
  _map[{std::atoi(t[1].c_str()), std::atoi(t[2].c_str())}].set_res(t);
}

void Client::initTab()
{
  _tab["msz"] = [&] (const std::vector<std::string> &t) { _msz(t);  };
  _tab["bct"] = [&] (const std::vector<std::string> &t) { _bct(t);  };
}

void Client::call(std::vector<std::string> const &t)
{
  	if (_tab.find(t[0]) != _tab.end())
	  _tab[t[0]](t);
}
