//
// Created by alice on 20/06/17.
//

#include "parser.hpp"

zappy::parser::parser() :
	_function_ptr({
			      {"help", [&] (int i) -> int {help_function(i); return 0;}},
			      {"flush", [&] (int i) -> int {flush_function(i); return 0;}},
		      })
{
  input.clear();
}

zappy::parser::~parser() {

}

int zappy::parser::lexer() {
  return 0;
}

int zappy::parser::help_function(int)
{
  std::cout << "  help  - Display this help" << std::endl;
  std::cout << "  flush - Flush the entry stack of the client" << std::endl;
  std::cout << "  quit  - Disconnect and terminate client connection" << std::endl;
  return 0;
}

int zappy::parser::flush_function(int)
{
  return 0;
}
