//
// Created by Jean-Adrien on 19/06/17.
//

#include <iostream>
#include <server.hpp>
#include "zappy.hpp"
#include "ZappyException.hpp"

zappy::Zappy::Zappy(int ac, char **av) {
    if (arg_entry(ac, av, &_arg) == 1)
        throw zappy::Exception("Error While loading arguments.");
    std::cout << "Client Zappy v0.1" << std::endl;
    std::cout << "PORT    : " << _arg.port << std::endl;
    std::cout << "TEAM    : " << _arg.team << std::endl;
    std::cout << "HOST    : " << _arg.host << std::endl;
    std::cout << name << ": settingUp cookie for connection to " << _arg.host << std::endl;
    if (cookie_setup(&_cook) == 1)
         throw zappy::Exception("Error while loading the zappy Connection Manager.");
    if (cookie_connect(&_cook, &_arg) == 1)
        throw zappy::Exception("Could not connect to the remote Host given.");
    _relay_manager.flag = 1;
}

zappy::Zappy::~Zappy() {
    if (_relay_manager.flag == 0)
        std::cout << name << ": Warnnig relay_manager Thread still Runnig." << std::endl;
    if (cookie_disconnect(&_cook) == 1)
        std::cout << "Failed to disconnect, Process will be ended with open socket." << std::endl;
    arg_free(&_arg);
}

void zappy::Zappy::run() {
    if (_relay_manager.flag == 0)
        throw zappy::Exception("Relay manager already running, quitting.");
    if (init_relay_connector(&_cook, &_fd_manager) == 1)
        throw zappy::Exception("Could not run project.");
    if (relay_manager_start(&_cook, &_fd_manager, &_relay_manager) == 1)
        throw  zappy::Exception("Could not run project.");
}

void zappy::Zappy::stop() {
    if (_relay_manager.flag == 1 || _relay_manager.flag == -1)
        std::cout << name << ": Relay manager not runnig." << std::endl;
    if (relay_manager_stop(&_relay_manager))
        throw zappy::Exception("Can not stop the relay_manager Thread.");
}

void zappy::Zappy::console() {
  std::cout << std::endl << "Wellcome to Zappy - console v0.1" << std::endl;
  std::cout << "Type help for more information" << std::endl;
  std::string input;
  input.clear();
  while (input.find("quit") != 0)
    {
      std::cout << _arg.team << " &>";
      if (!std::getline(std::cin, input))
	{
	  std::cout << std::endl;
	  return ;
	}
      try {
	  if (!input.empty())
	    _parser.lexer(input);
	} catch (...) {
	  std::cerr << "Unknown command" << std::endl;
	}
      input.clear();
    }

}

const t_arg &zappy::Zappy::getArgs() const
{
  return _arg;
}
