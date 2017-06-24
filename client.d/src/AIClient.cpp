//
// Created by vincent on 24/06/17.
//

#include <server.hpp>
#include <iostream>
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

zappy::AIClient::AIClient(const t_arg &args) : _args(args)
{
  char *str;

  while (!(str = srv_read()));
  std::cout << "J'ai reçu " << str << std::endl;
  srv_write(this->_args.team);
  while (!(str = srv_read()));
  std::cout << "J'ai reçu " << str << std::endl;
  _getWorldInformation(str);
  _play();

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

void zappy::AIClient::_play()
{

}
