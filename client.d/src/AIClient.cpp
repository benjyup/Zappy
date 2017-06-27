//
// Created by vincent on 24/06/17.
//

#include <server.hpp>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <string>
#include "AIClient.hpp"


const std::vector<zappy::AIClient::SIncantation>	zappy::AIClient::INCANTATIONS = {
	{1, { {LINEMATE, 1}, {DERAUMERE, 0}, {SIBUR, 0}, {MENDIANE, 0}, {PHIRAS, 0}, {THYSTAME, 0} } },
	{2, { {LINEMATE, 1}, {DERAUMERE, 1}, {SIBUR, 1}, {MENDIANE, 0}, {PHIRAS, 0}, {THYSTAME, 0} } },
	{2, { {LINEMATE, 2}, {DERAUMERE, 0}, {SIBUR, 1}, {MENDIANE, 0}, {PHIRAS, 2}, {THYSTAME, 0} } },
	{4, { {LINEMATE, 1}, {DERAUMERE, 1}, {SIBUR, 2}, {MENDIANE, 0}, {PHIRAS, 1}, {THYSTAME, 0} } },
	{4, { {LINEMATE, 1}, {DERAUMERE, 2}, {SIBUR, 1}, {MENDIANE, 3}, {PHIRAS, 0}, {THYSTAME, 0} } },
	{6, { {LINEMATE, 1}, {DERAUMERE, 2}, {SIBUR, 3}, {MENDIANE, 0}, {PHIRAS, 1}, {THYSTAME, 0} } },
	{6, { {LINEMATE, 2}, {DERAUMERE, 2}, {SIBUR, 2}, {MENDIANE, 2}, {PHIRAS, 2}, {THYSTAME, 1} } },
};

const 	std::unordered_map<t_resource, std::string, std::hash<int>>	zappy::AIClient::RESOURCES_TO_STR = {
	{FOOD, "food"},
	{LINEMATE, "linemate"},
	{DERAUMERE, "deraumere"},
	{SIBUR, "sibur"},
	{MENDIANE, "mendiane"},
	{PHIRAS, "phiras"},
	{THYSTAME, "thystame"}
};

const 	std::unordered_map<std::string, t_resource>	zappy::AIClient::STR_TO_RESOURCES = {
	{"food", FOOD},
	{"linemate", LINEMATE},
	{"deraumere", DERAUMERE},
	{"sibur", SIBUR},
	{"mendiane", MENDIANE},
	{"phiras", PHIRAS},
	{"thystame", THYSTAME}
};

void zappy::AIClient::ProxyRegister(Proxy *prox, int x, int y) {
  _prox = prox;
  _worldDimension.first = x;
  _worldDimension.second = y;

}

zappy::AIClient::AIClient(const t_arg &args) :
	_level(0),
	_args(args),
	_incantationLevel(0),
	_prox(NULL)
{
  /* char *str;

   while (!(str = srv_read()));
   std::cout << "J'ai reçu " << str << std::endl;
   srv_write(this->_args.team);
   while (!(str = srv_read()));
   std::cout << "J'ai reçu " << str << std::endl;
   _getWorldInformation(str);
   _play();*/

}

zappy::AIClient::~AIClient()
{
  std::cerr << "~AIClient" << std::endl;
}

void zappy::AIClient::_getWorldInformation(const std::string &informations)
{
  try {
      _clietnNum = std::stoul(informations.substr(0, informations.find('\n')));
      _worldDimension.first = std::stoul(informations.substr(informations.find(' ')));
      _worldDimension.second = std::stoul(informations.substr(informations.find(' '), informations.size() - 1));
    } catch (std::exception) {
      throw std::runtime_error("Error while getting world informations.");
    }

  std::cout << "clientNum = " << _clietnNum << std::endl;
  std::cout << "X = " << _worldDimension.first << std::endl;
  std::cout << "Y = " << _worldDimension.second << std::endl;
}

void 			zappy::AIClient::_play()
{
  std::string		response;
  char			*str;

  std::cout << "_play" << std::endl;
  //_whatdoINeed();
  _getInventory();
  _look();
  std::cout << "_play" << std::endl;
  while (response != "dead\n")
    {
      if ((str = srv_read()) != nullptr)
	{
	  std::cout << "response = " << str << std::endl;
	  response = str;
	}
    }
  std::cout << "fin" << std::endl;
}

void 			zappy::AIClient::_eat()
{

}

void 			zappy::AIClient::_getInventory()
{
  char			*str;

  srv_write("Inventory");
  if (!(str = srv_read()))
    {
      std::cout << "JE QUITTE" << std::endl;
      return ;
    }

  std::string tmp(str);

  tmp.erase(std::remove_if(tmp.begin(),
			   tmp.end(),
			   [](auto c) {
			     return (c == '[' || c == ']' || c == ',');
			   }),
	    tmp.end());



  std::string t(tmp);
  std::transform(tmp.begin(), tmp.end(), tmp.begin(),
		 [](auto c) { return std::tolower(c);});

  std::stringstream	ss(tmp);
  for (int i = 0 ; i  < NBR_OF_RESOURCES ; ++i)
    {
      ss >> tmp;
      ss >> _inventory[STR_TO_RESOURCES.at(tmp)];
    }

  std::cout << str << std::endl;
  std::cout << t << std::endl;
  std::cout << tmp << std::endl;
  std::cout << "Inventaire: " << std::endl;
  for (const auto &it : _inventory)
    {
      std::cout << "- "<< it.first << " " << RESOURCES_TO_STR.at(it.first) << ": " << it.second << std::endl;
    }
}

void 		zappy::AIClient::_look()
{
  int 		i = 0;

  while (i < _currentLook.size())
    {
      for (const auto &resource : _currentLook[i])
	{
	  if (resource.second > 0 && _isNeeded(resource.first));
	}
      i += 1;
    }
}

void 			zappy::AIClient::_makeInventory(const std::string &resources)
{
  std::stringstream 	ss(resources);
  std::string		str;

  std::cout << "_makeInventory" << std::endl;
  while (ss)
    {
      ss >> str;
      std::cout << str << std::endl;
    }
}

bool zappy::AIClient::_isNeeded(t_resource resource)
{
  return   INCANTATIONS[_level].resources.find(resource)->second > 0;
}

zappy::RequestType zappy::AIClient::updade() {
  if (_prox == NULL)
    return zappy::NOOP;
  return zappy::FORWARD;
}
