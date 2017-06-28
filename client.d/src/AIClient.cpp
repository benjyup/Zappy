//
// Created by vincent on 24/06/17.
//

#include <server.hpp>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "mendatory/AIClient.hpp"


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
	_prox(NULL),
	_mode(true)
{
  //_todo.push_back(LOOK);
  _todo.push_back(FORWARD);
  _todo.push_back(FORWARD);
  _todo.push_back(FORWARD);
}

void zappy::AIClient::setInventory(const std::unordered_map<t_resource, size_t, std::hash<int>> &newInventory)
{
  _currentInventory = newInventory;
}

void zappy::AIClient::setLook(const std::vector<std::unordered_map<t_resource, size_t, std::hash<int>>> &currentLook)
{
  _currentLook = currentLook;
}

zappy::AIClient::~AIClient()
{
  std::cerr << "~AIClient" << std::endl;
}

void 			zappy::AIClient::_play()
{
  std::string		response;
  char			*str;

  std::cout << "_play" << std::endl;
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
      ss >> _currentInventory[STR_TO_RESOURCES.at(tmp)];
    }

  std::cout << str << std::endl;
  std::cout << t << std::endl;
  std::cout << tmp << std::endl;
  std::cout << "Inventaire: " << std::endl;
  for (const auto &it : _currentInventory)
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
	  if (resource.second > 0 && _isNeeded(resource.first))
	    {
	      _go(i);
	      return ;
	    }
	}
      i += 1;
    }
}

void 			zappy::AIClient::_go(unsigned int tile_number)
{
  int           	i = 0;
  int           	first = 0;
  int           	middle = 0;
  int           	length = 1;
  int           	inc = 2;
  int 			move;

  while (i < 3 && tile_number >= first + length)
    {
      first += length;
      length += 2;
      middle += inc;
      inc += 2;
      i += 1;
    }
  while (i-- > 0)
    _todo.push_back(FORWARD);
  move = middle - tile_number;
  if (move > 0)
    _todo.push_back(LEFT);
  else if (move < 0)
      _todo.push_back(RIGHT);
  while (move-- > 0)
    _todo.push_back(FORWARD);
}

bool			zappy::AIClient::_isNeeded(t_resource resource)
{
  size_t 		nbr_of_resources = INCANTATIONS[_level].resources.find(resource)->second;

  return  nbr_of_resources > 0 && _currentInventory.find(resource)->second < resource;
}

zappy::RequestType 	zappy::AIClient::update(std::string input) {
  RequestType		request = NOOP;

  if (_prox == NULL)
    return request;

    if (!input.empty())
        std::cout << "J'ai recu :" << input << std::endl;
  if (_mode)
    {
    //  std::cout << "MODE ECRITURE" << std::endl;
      if (!(_todo.empty()))
	{
	  std::cout << "Je pop" << std::endl;
	  request = _todo.front();
	  _todo.pop_front();
	}
    }
  else
    {
    //  std::cout << "MODE LECTURE" << std::endl;
    }
  _mode = !_mode;
  return request;
}
