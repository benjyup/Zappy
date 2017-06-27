//
// Created by alice on 20/06/17.
//

#include <server.hpp>
#include "parser.hpp"

zappy::parser::parser() :
	_function_ptr({
			      {"help", [&] (const std::string &str) -> int { return help_function(str);}},
			      {"flush", [&] (const std::string &str) -> int { return flush_function(str);}},
			      {"send", [&] (const std::string &str) -> int {srv_write(str.c_str()); return 0;}},
                  {"quit", [&] (const std::string &str) -> int {exit(0);}},
                  {"read", [&] (const std::string &str) -> int {char *s =  srv_read();if (s != NULL) std::cout << s << std::endl; return 0;}},
                  {"noop", [&] (const std::string &str) -> int {return 0;}},
		      })
{
  input.clear();
}

zappy::parser::~parser() {

}


int 			zappy::parser::lexer(const std::string &cmd) {
  unsigned long		first_ws = cmd.find(" ");
  std::string		cmd_name = cmd.substr(0,  first_ws);
  std::string		cmd_args;

  if (first_ws != std::string::npos)
    cmd_args = cmd.substr(first_ws + 1);
  //std::cerr << "cmd_name = " << cmd_name << ",  cmd_args = " << cmd_args << std::endl;
  return _function_ptr[cmd_name](cmd_args);
}

int 			zappy::parser::help_function(const std::string &)
{
  std::cout << "  help  - Display this help" << std::endl;
  std::cout << "  flush - Flush the entry stack of the client" << std::endl;
  std::cout << "  quit  - Disconnect and terminate client connection" << std::endl;
  return 0;
}


int 			zappy::parser::flush_function(const std::string &)
{
    std::string msg = srv_read();

    while (!msg.empty()) {
        std::cout << msg << std::endl;
        msg = srv_read();
    }
    return 0;
}
