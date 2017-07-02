//
// Created by kyxo on 6/19/17.
//

#include <vector>
#include <string>
#include <sstream>
#include "server.hpp"
#include "zappy.hpp"
#include "Client.hpp"

int             main(int ac, char **av)
{
  try
    {
      zappy::Zappy project(ac, av);
      char *buf;
      std::string s;
      std::vector<std::string>	tab;

      Client::Client c(project);
      c.initTab();

      while (c.is_running())
	{
	  c.update();
	  buf = srv_read();
	  if (buf)
	    {
	      std::cerr << buf << std::endl;
	      s.assign(buf);
	      c.getTab(s, tab);
	      c.call(tab);
	      s.clear();
	    }
	}
    }
  catch (std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      return 1;
    }
  //  cleanup the engine
  return 0;
}