//
// Created by Jean-Adrien on 27/06/17.
//

#include <vector>
#include <string>
#include "Request.hpp"

zappy::Request::Request(RequestType type): _type(type),
					   _function_ptr({
								 {zappy::FORWARD, [&] (std::string &str) -> int {
								   if (!str.empty())
								     {
								       if (str.find("ok") != std::string::npos)
									 return 0;
								     }
								   return 1;
								 }}
							 })
{

}

zappy::Request::~Request() {

}

int zappy::Request::execute(std::string &str)
{
  return _function_ptr[_type](str);
}