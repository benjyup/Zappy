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
	{PLAYER, "player"},
	{LINEMATE, "linemate"},
	{DERAUMERE, "deraumere"},
	{SIBUR, "sibur"},
	{MENDIANE, "mendiane"},
	{PHIRAS, "phiras"},
	{THYSTAME, "thystame"}
};

const 	std::unordered_map<std::string, t_resource>			zappy::AIClient::STR_TO_RESOURCES = {
	{"food", FOOD},
	{"player", PLAYER},
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
			{zappy::RequestType::BROADCAST, [&] (const std::string &str){_broadcastAction(str);}},
			{zappy::RequestType::INVENTORY, [&] (const std::string &str){_inventoryAction(str);}},
			{zappy::RequestType::INCANTATION, [&] (const std::string &str){_incantationAction(str);}},
			{zappy::RequestType::INCANTATION_VOID, [&] (const std::string &){}}
		}
	),
	_deplacement({
			     {1, [&] (){_todo.push_front(FORWARD);}},
			     {2, [&] (){
			       _todo.push_front(FORWARD);
			       _todo.push_front(LEFT);
			       _todo.push_front(FORWARD);
			     }},
			     {3, [&] (){
			       _todo.push_front(FORWARD);
                     _todo.push_front(LEFT);
			     }},
			     {4, [&] (){
                     _todo.push_front(FORWARD);
			       _todo.push_front(LEFT);
			       _todo.push_front(FORWARD);
			       _todo.push_front(LEFT);
			     }},
			     {5, [&] (){
                     _todo.push_front(FORWARD);
			       _todo.push_front(LEFT);
			       _todo.push_front(LEFT);
			     }},
			     {6, [&] (){
                     _todo.push_front(FORWARD);
			       _todo.push_front(RIGHT);
			       _todo.push_front(FORWARD);
			       _todo.push_front(RIGHT);
			     }},
                 {7, [&] (){
                     _todo.push_front(FORWARD);
                     _todo.push_front(RIGHT);
                 }},
			     {8, [&] (){
			       _todo.push_front(FORWARD);
			       _todo.push_front(RIGHT);
			       _todo.push_front(FORWARD);
			     }}
		     }
	),
	_outputSave(""),
	_broadcastCyle(0)
{
  _initInventory(_currentInventory);
  _todo.push_back(INVENTORY);
}


zappy::AIClient::~AIClient()
{
  //std::cerr << "~AIClient" << std::endl;
}

void 			zappy::AIClient::_play()
{
  std::string		response;
  char			*str;

  //std::cout << "_play" << std::endl;
  _look();
  //std::cout << "_play" << std::endl;
  while (response != "dead\n")
    {
      if ((str = srv_read()) != nullptr)
	{
	  //std::cout << "response = " << str << std::endl;
	  response = str;
	}
    }
  //std::cout << "fin" << std::endl;
}

void 			zappy::AIClient::_getInventory(const std::string &data)
{
  std::string tmp(data);

  std::cout << "ici" << std::endl;
  tmp.erase(std::remove_if(tmp.begin(),
			   tmp.end(),
			   [](auto c) {
			     return (c == '[' || c == ']' || c == ',');
			   }),
	    tmp.end());
  std::cout << "ici" << std::endl;



  std::string t(tmp);
  std::cout << "ici" << std::endl;
  std::transform(tmp.begin(), tmp.end(), tmp.begin(),
		 [](auto c) { return std::tolower(c);});
  std::cout << "ici" << std::endl;

  std::stringstream	ss(tmp);
  int i = 0;
  while (i < NBR_OF_RESOURCES && !tmp.empty())
    {
      std::cout << "TMP = " << tmp << std::endl;
      ss >> tmp;
      ss >> _currentInventory[STR_TO_RESOURCES.at(tmp)];
      i += 1;
    }
  std::cout << "Inventaire: " << std::endl;
  for (const auto &it : _currentInventory)
    {
      std::cout << "- "<< it.first << " " << RESOURCES_TO_STR.at(it.first) << ": " << it.second << std::endl;
    }
  std::cout << " ---------------- " << std::endl;
}

void 		zappy::AIClient::_look()
{
  int 		i = 0;

  //std::cout << "LOOK" << std::endl;
  while (i < _currentLook.size())
    {
      for (const auto &resource : _currentLook[i])
	{
	  if (resource.second > 0 && _isNeeded(resource.first))
	    {
	      //std::cout << "GO" << std::endl;
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
  move = _moveCalculate(middle, tile_number);
  std::size_t howManyResources = _howManyResourses(resource, tile_number);
  std::cout << "JE PREND " << howManyResources << " " << RESOURCES_TO_STR.at(resource) << std::endl;
  for (int i = 0 ;  i < howManyResources ; ++i)
    _todo.push_back(RESOURCE_TO_REQUEST.at(resource));
  //std::cout << "go to tile[" << tile_number << "] with " << _todo.size() << " move(s)" << std::endl;
}

void 			zappy::AIClient::_go(const unsigned int pos)
{
    _todo.clear();
  _deplacement[pos]();
}

bool			zappy::AIClient::_isNeeded(const t_resource resource) const
{
  if (resource == FOOD)
    {
      std::cout << "FOOD = " << _currentInventory.at(FOOD) << std::endl;
      if (_currentInventory.at(FOOD) <= 5)
	std::cout << "JAI BESOIN DE MANGER" << std::endl;
      return  _currentInventory.at(FOOD) <= 5;
    }
  auto res = INCANTATIONS[_level].resources.find(resource);
  if (res == INCANTATIONS[_level].resources.end())
    return false;

  size_t 		nbr_of_resources = INCANTATIONS[_level].resources.find(resource)->second;

  return  nbr_of_resources > 0 && _currentInventory.find(resource)->second < resource;
}

std::vector<t_inventory> 						zappy::AIClient::_lookParse(const std::string &str)
{
  std::vector<t_inventory >   look;
  std::size_t                                                           pos = 0, begin = 0;
  t_inventory                                    			inventory;
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

void                                           zappy::AIClient::_initInventory(t_inventory &inventory)
{
  inventory[FOOD] = 0;
  inventory[LINEMATE] = 0;
  inventory[DERAUMERE] = 0;
  inventory[SIBUR] = 0;
  inventory[MENDIANE] = 0;
  inventory[PHIRAS] = 0;
  inventory[THYSTAME] = 0;
  inventory[PLAYER] = 0;
}

zappy::RequestType 	zappy::AIClient::update(std::string output) {
  RequestType		request = NOOP;

  if (_prox == NULL)
    return request;

  static int a = 0;
  if (a == 0)
    {
      _broadcast();
      a += 1;
    }

  if (_mode)
    {
      if (!(_todo.empty()))
	{
	  request = _todo.front();
	  std::cout << "Je pop" << std::endl;
	  std::cout << "requete = " << request << std::endl;
	  _OutputType.push_back(request);
	  _todo.pop_front();
	}
      else
	{
/*
	  _mode = !_mode;
	  _todo.push_back(INVENTORY);
*/
	}
      _mode = !_mode;
    }
  else
    {
      if (!output.empty() && _OutputType.size() != 0)
	{
	  std::cout << "J'ai recu :" << output << std::endl;
	  if (output.find("message") != std::string::npos)
	    {
	      _messageAction(output);
	    }
	  else if (!_OutputType.empty())
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
  std::string str = output;

/*
  if (str.back() != ']')
    {
      this->_outputSave += str;
      this->_OutputType.push_front(LOOK);
      _mode = !_mode;
      return ;
    }
  if (!_outputSave.empty())
    str = _outputSave;
*/
  if (str[0] == '[')
    {
      std::cout << "GET LOOK :" << str << std::endl;
      _currentLook = _lookParse(str);
      _look();
      std::cout << "_todo.size = " << _todo.size() << std::endl;
      //_isInventoryData = true;
      //_addTodo(INVENTORY);
      _todo.push_back(INVENTORY);
      _outputSave.clear();
    }
}

void zappy::AIClient::_inventoryAction(const std::string &output)
{
  std::string str(output);

/*
  if (str.back() != ']')
    {
      this->_outputSave += str;
      this->_OutputType.push_front(INVENTORY);
      _mode = !_mode;
      return ;
    }
  if (!_outputSave.empty())
    str = _outputSave;
*/
  if (str[0] == '[')
    {
      std::cout << "GET INVENTORY" << std::endl;
      _getInventory(str);
      std::cout << "_ready = " << std::boolalpha << _readyFoIncantation() << std::endl;
      if (_readyFoIncantation())
	{
	  std::cout << "PRET POUR LINCANTATION" << std::endl;
	  _takeUselessObject();
	  _setObjectDown();
	  _todo.push_back(RequestType::INCANTATION);
	  _todo.push_back(INCANTATION_VOID);
	}
      else
	{
	  std::cout << "PAS PRET POUR LINCANTATION" << std::endl;
	  _todo.push_back(LOOK);
	}
      _outputSave.clear();
    }
}

void zappy::AIClient::_randomDirection()
{
  std::array<RequestType, 2> 	directions = {RIGHT, LEFT};
  int 				random = rand() % 2;

  _todo.push_back(directions[random]);
  int max = rand() % 5 + 1;
  for (int i = 0 ; i < max ; ++i)
    _todo.push_back(FORWARD);
}

std::size_t 	zappy::AIClient::_howManyResourses(const t_resource resource, const int tile_number) const
{
  if (resource != FOOD)
    return (INCANTATIONS.at(_level).resources.at(resource) <= _currentLook.at(tile_number).at(resource)) ? (INCANTATIONS.at(_level).resources.at(resource)) : (_currentLook.at(tile_number).at(resource));
  else
    return _currentLook.at(tile_number).at(FOOD);

}

int zappy::AIClient::_moveCalculate(const int middle, const int tile_number)
{
  int move = middle - tile_number;

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
  return 0;
}

bool 				zappy::AIClient::_readyFoIncantation()
{
  const SIncantation		&incantation = INCANTATIONS[_level];

  for (auto &resource : incantation.resources)
    {
      if(resource.second != 0 && _currentInventory.at(resource.first) < resource.second)
	{
	  std::cout << "RETURN FALSE" << std::endl;
	  return false;
	}
    }
  if (_currentLook.at(0).find(PLAYER) == _currentLook.at(0).end())
    std::cout << "YA PAS DE PLAYER" << std::endl;
  if (_currentLook.at(0).at(PLAYER) != incantation.nbOfPlayers)
    {
      std::cout << "PAS ASSEZ DE PLAYER" << std::endl;
      if (_broadcastCyle++ >= (_worldDimension.first + _worldDimension.second) / 1.5)
	{
/*
	  std::cout << "JE FORK" << std::endl;
	  _todo.push_back(FORK);
	  _todo.push_back(INCANTATION);
	  _todo.push_back(INCANTATION_VOID);
*/
	  _broadcastCyle = 0;
	}
      return false;
    }
  return _currentInventory.at(FOOD) > 300 / 126;
}

void zappy::AIClient::_incantationAction(const std::string &output)
{
  std::cout << "_incantationAction" << std::endl;
  if (output != "ko")
    {
      std::cout << "INCANTATION REUSSIE" << std::endl;
      this->_level += 1;
      _broadcastCyle = 0;
    }
  else
    std::cout << "INCANTATION RATEE" << std::endl;
  _todo.push_back(INVENTORY);
}

void zappy::AIClient::_setObjectDown()
{
  RequestType requestType;

  for (auto &it : AIClient::INCANTATIONS.at(_level).resources)
    {
      switch(it.first)
	{
	  case LINEMATE:
	    {
	      std::cout << "JE SET LINEMATE" << std::endl;
	      requestType = SET_LINEMATE;
	    }
	  break;
	  case DERAUMERE:
	    requestType = SET_DERAUMERE;
	  break;
	  case SIBUR:
	    requestType = SET_SIBUR;
	  break;
	  case MENDIANE:
	    requestType = SET_MENDIANE;
	  break;
	  case PHIRAS:
	    requestType = SET_PHIRAS;
	  break;
	  case THYSTAME:
	    requestType = SET_THYSTAME;
	  break;
	}
      for (int i = 0 ; i < it.second ; ++i)
	_todo.push_back(requestType);
    }
}


void zappy::AIClient::_broadcast() {
  std::cout << "pass in broadcast" << std::endl;
  _todo.push_back(BROADCAST);
}

void 			zappy::AIClient::_takeUselessObject()
{
  const SIncantation &incantation = INCANTATIONS.at(_level);

  for (auto &it : incantation.resources)
    {
      if (it.second == 0 || it.second != _currentLook[0][it.first])
	{
	  int i = 0;
	  while (i < _currentLook[0][it.first])
	    {
	      std::cout << "i = " << i << std::endl;
	      _todo.push_back(RESOURCE_TO_REQUEST.at(it.first));
	      i += 1;
	    }
	}
    }
}

void zappy::AIClient::_broadcastAction(const std::string &str) {
  std::cout << "Broadcast : " << str << std::endl;
}

void zappy::AIClient::_messageAction(const std::string &str) {

  std::string extract = str;
  extract.erase(extract.begin(), extract.begin()+extract.find("!"));
  extract = _my_decrypt(extract);
  if (extract.find(_args.team) == std::string::npos)
    std::cout << "message receive : note my team message" << std::endl;
  else
    std::cout << "message receive : " << extract << std::endl;
  if (extract.find("INCANTATION") != std::string::npos)
    {
      std::string direction = str;
      direction.erase(direction.begin(), direction.begin() + direction.find(" "));
      int dir = std::atoi(direction.c_str());
      std::cout << dir << std::endl;
      _go(dir);
    }
}

std::string zappy::AIClient::_my_decrypt(const std::string &str) {
  std::string data = str;

  int i = 1;
  while (data[i])
    {
      data[i] -= 12;
      i += 1;
    }
  return data;
}
