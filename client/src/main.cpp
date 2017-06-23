//
// Created by kyxo on 6/19/17.
//

//void is::GameEngine::Init(const char* title, int width, int height,
//			  int bpp, bool fullscreen)
//{
//  this->_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(width, height), bpp,
//				    fullscreen, false, false, 0);
//  this->_driver = this->_device->getVideoDriver();
//  this->_smgr = this->_device->getSceneManager();
//  this->_guienv = this->_device->getGUIEnvironment();
//  irr::core::stringw wStr(title);
//  this->_device->setWindowCaption(wStr.c_str());
//
//  this->_fullscreen = fullscreen;
//  this->_running = true;
//}

//  try {
//      std::shared_ptr<is::GameEngine> engine = std::make_shared<is::GameEngine>("Indie Studio",
//										1900, 1000, 0, true);
//      engine->PushState(new is::IntroState);
//
//      irr::core::array<irr::SJoystickInfo> joystickInfo;
//      engine->getDevice()->activateJoysticks(joystickInfo);
//      while (engine->Running())
//	{
//	  engine->HandleEvents();
//	  engine->Update();
//	  engine->Draw();
//	}
//    } catch (const std::exception &e) {
//      if (!std::string(e.what()).empty())
//	std::cerr << "Error: " << e.what() << std::endl;
//    }

#include <vector>
#include <unistd.h>
#include <string>
#include <string.h>
#include <sstream>
#include <Ressource.hpp>
#include "zappy.hpp"
#include "server.hpp"
#include "Client.hpp"

int             main(int ac, char **av) {

//try
//  {
 //   zappy::Zappy project(ac, av);
    std::stringstream	ssin;
    std::vector<std::string> tab;
  char 			*buf;
  std::string		s;

//    project.run();
    Client::Client c;
    c.initTab();
    while (c.is_running())
      {
//	buf = srv_read();
//	if (buf)
//	  {
//	    s.assign(buf);
//	    c.getTab(s, tab);
//	    c.call(tab);
//	    s.clear();
//	    //c.update;
//	  }
	c.update();

      }
   // project.stop();
//  }
//  catch (std::exception &e)
//    {
//      std::cerr << e.what() << std::endl;
//      return 1;
//    }
  // cleanup the engine
  return 0;
}