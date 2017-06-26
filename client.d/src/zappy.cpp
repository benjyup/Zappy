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
}

zappy::Zappy::~Zappy() {
  if (cookie_disconnect(&_cook) == 1)
    std::cout << "Failed to disconnect, Process will be ended with open socket." << std::endl;
  arg_free(&_arg);
}

int zappy::Zappy::update() {
    if (connection_handler(&_cook, &_fd_manager) == 1)
        return 1;
//  char *str;
//while (!(str = srv_read()));
//  std::cout << "J'ai reçu " << str << std::endl;
//  srv_write(this->_arg.team);
//  while (!(str = srv_read()));
 // std::cout << "J'ai reçu " << str << std::endl;
    return 0;
}

void zappy::Zappy::console() {
 // std::cout << std::endl << "Wellcome to Zappy - console v0.1" << std::endl;
 // std::cout << "Type help for more information" << std::endl;
  std::string input;
  input.clear();
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
