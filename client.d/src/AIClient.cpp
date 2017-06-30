//
// Created by vincent on 24/06/17.
//

#include <server.hpp>
#include <iostream>
#include <sstream>
#include <algorithm>
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

const 	std::unordered_map<std::string, t_resource>			zappy::AIClient::STR_TO_RESOURCES = {
	{"food", FOOD},
	{"linemate", LINEMATE},
	{"deraumere", DERAUMERE},
	{"sibur", SIBUR},
	{"mendiane", MENDIANE},
	{"phiras", PHIRAS},
	{"thystame", THYSTAME}
};

const std::unordered_map<t_resource, zappy::RequestType, std::hash<int>>		zappy::AIClient::RESOURCE_TO_REQUEST = {
	{FOOD, TAKE_FOOD},
	{LINEMATE, TAKE_LINEMATE},
	{DERAUMERE, TAKE_DERAUMERE},
	{SIBUR, TAKE_SIBUR},
	{MENDIANE, TAKE_MENDIANE},
	{PHIRAS, TAKE_PHIRAS},
	{THYSTAME, TAKE_THYSTAME}
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
	_mode(true),
	_isInventoryData(true),
	_actions(
		{
			{zappy::RequestType::LOOK, [&] (const std::string &str){_lookAction(str);}},
			{zappy::RequestType::INVENTORY, [&] (const std::string &str){_inventoryAction(str);}}
		}
	)
{

  _initInventory(_currentInventory);

  //_addTodo(INVENTORY);

  _todo.push_back(INVENTORY);

  //_todo.push_back(FORWARD);
  //_todo.push_back(FORWARD);
  //_todo.push_back(FORWARD);
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

void 			zappy::AIClient::_getInventory(const std::string &data)
{
  std::string tmp(data);

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

  std::cout << "Inventaire: " << std::endl;
  for (const auto &it : _currentInventory)
    {
      std::cout << "- "<< it.first << " " << RESOURCES_TO_STR.at(it.first) << ": " << it.second << std::endl;
    }
}

void 		zappy::AIClient::_look()
{
  int 		i = 0;

  std::cout << "LOOK" << std::endl;
  while (i < _currentLook.size())
    {
      for (const auto &resource : _currentLook[i])
	{
	  if (resource.second > 0 && _isNeeded(resource.first))
	    {
	      std::cout << "GO" << std::endl;
	      _go(i, resource.first);
	      return ;
	    }
	}
      i += 1;
    }
  _randomDirection();
}

void 			zappy::AIClient::_go(const unsigned int tile_number, const t_resource resource)
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
  std::cout << "move = " << move;
  std::cout << " midlle = " << middle;
  std::cout << " tile_number = " << tile_number << std::endl;
  if (move > 0)
    _todo.push_back(LEFT);
  else if (move < 0)
      {
	move = move * -1;
	_todo.push_back(RIGHT);
      }
  if (move != 0)
    while (move-- > 0)
      _todo.push_back(FORWARD);

  std::size_t how_many_resources;
  if (resource != FOOD)
    how_many_resources = (INCANTATIONS.at(_level).resources.at(resource) <= _currentLook[tile_number][resource]) ? (INCANTATIONS.at(_level).resources.at(resource)) : (_currentLook[tile_number][resource]);
  else
    how_many_resources = _currentLook[tile_number][FOOD];

  int max = how_many_resources;
  std::cout << "JE PREND " << how_many_resources << " " << RESOURCES_TO_STR.at(resource) << std::endl;
  for (int i = 0 ;  i < max ; ++i)
    _todo.push_back(RESOURCE_TO_REQUEST.at(resource));
  std::cout << "go to tile[" << tile_number << "] with " << _todo.size() << " move(s)" << std::endl;
}

bool			zappy::AIClient::_isNeeded(t_resource resource)
{
  if (resource == FOOD)
    {
      if (_currentInventory[FOOD] <= 5)
	std::cout << "JAI BESOIN DE MANGER" << std::endl;
      return  _currentInventory[FOOD] <= 5;
    }
  auto res = INCANTATIONS[_level].resources.find(resource);
  if (res == INCANTATIONS[_level].resources.end())
    return false;

  size_t 		nbr_of_resources = INCANTATIONS[_level].resources.find(resource)->second;

  return  nbr_of_resources > 0 && _currentInventory.find(resource)->second < resource;
}

std::vector<std::unordered_map<t_resource, size_t,
	std::hash<int>>> 						zappy::AIClient::_lookParse(const std::string &str)
{
  std::vector<std::unordered_map<t_resource, size_t, std::hash<int>>>   look;
  std::size_t                                                           pos = 0, begin = 0;
  std::unordered_map<t_resource, size_t,
	  std::hash<int>>                                    		inventory;
  std::string 								tmp(str.substr(begin, pos - begin));


  while ((pos = str.find_first_of(",", pos + 1)) != std::string::npos)
    {
      tmp = str.substr(begin, pos - begin);
      std::stringstream ss(tmp);

      _extractResources(tmp, inventory);
      look.push_back(inventory);
      begin = pos + 1;
    }
  tmp = str.substr(begin, pos);
  _extractResources(tmp, inventory);
  look.push_back(inventory);
  return look;
}

void                                            zappy::AIClient::_extractResources(const std::string &str,
										   t_inventory &inventory)
{
  std::string                                   tmp(str);
  std::stringstream                             ss(tmp);

  _initInventory(inventory);
  while (ss >> tmp)
    try { inventory[STR_TO_RESOURCES.at(tmp)] +=  1; } catch (...) {	}
}

void                                           zappy::AIClient::_initInventory(std::unordered_map<t_resource, size_t,
	std::hash<int>> &inventory)
{
  inventory[FOOD] = 0;
  inventory[LINEMATE] = 0;
  inventory[DERAUMERE] = 0;
  inventory[SIBUR] = 0;
  inventory[MENDIANE] = 0;
  inventory[PHIRAS] = 0;
  inventory[THYSTAME] = 0;
}

zappy::RequestType 	zappy::AIClient::update(std::string output) {
  RequestType		request = NOOP;

  if (_prox == NULL)
    return request;

  if (_mode)
    {
      if (!(_todo.empty()))
	{
	  std::cout << "Je pop" << std::endl;
	  std::cout << "requete = " << request << std::endl;
	  request = _todo.front();
	  _OutputType.push_back(request);
	  _todo.pop_front();
	}
      _mode = !_mode;
    }
  else
    {
      if (!output.empty())
	{
	  std::cout << "J'ai recu :" << output << std::endl;
	  if (!_OutputType.empty())
	    {
	      try { _actions[_OutputType.front()](output); } catch (...) { }
	      _OutputType.pop_front();
	    }
	  _mode = !_mode;
	}
    }
  return request;
}

void zappy::AIClient::_addTodo(const zappy::RequestType requestType)
{
  this->_todo.push_back(requestType);
  this->_OutputType.push_back(requestType);
}


void zappy::AIClient::_lookAction(const std::string &output)
{
  if (output[0] == '[')
    {
      std::cout << "GET LOOK :" << output << std::endl;
      _currentLook = _lookParse(output);
      _look();
      std::cout << "_todo.size = " << _todo.size() << std::endl;
      //_isInventoryData = true;
      //_addTodo(INVENTORY);
      _todo.push_back(INVENTORY);
    }
}

void zappy::AIClient::_inventoryAction(const std::string &output)
{
  if (output[0] == '[')
    {
      std::cout << "GET INVENTORY" << std::endl;
      _getInventory(output);
      //_isInventoryData = false;
      //_addTodo(LOOK);
      _todo.push_back(LOOK);
    }
}

void zappy::AIClient::_randomDirection()
{
  std::array<RequestType, 2> 	directions = {RIGHT, LEFT};
  int 				random = rand() % 2;

  _todo.push_back(directions[random]);
  int max = rand() % 3 + 1;
  for (int i = 0 ; i < max ; ++i)
    _todo.push_back(FORWARD);
}
