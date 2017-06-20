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
#include <string.h>
#include <sstream>
#include "Client.hpp"

int             main(int ac, char **av) {

  std::string	s;
  char 		buf[4096];
  ssize_t 	ret;
  std::stringstream	ssin;
  std::vector<std::string> tab;
  Client::Client		c;

  memset(buf, 0, 4096);
  c.initTab();
  if (ac == 2 && !strcasecmp("-help", av[1]))
    {
      std::cerr << "USAGE: " << av[0] << " -p port -n name -h machine" << std::endl;
      std::cerr << "        port    is the port number" << std::endl;
      std::cerr << "        name    is the name of the team" << std::endl;
      std::cerr << "        machine is the name of the machine; localhost by default" << std::endl;
      return 0;
    }
//  if (ac != 7)
//    {
//      std::cerr << "USAGE: " << av[0] << " -p port -n name -h machine" << std::endl;
//      return 0;
//    }
  while ((ret = read(0, buf, 4096)) > 0) // appel de la fonction read de ja
    {
      ssin.clear();
      buf[ret] = 0;
      ssin.write(buf, strlen(buf));
      tab.clear();
      while (ssin.good())
	{
	  std::string word;
	  ssin >> word;
	  tab.push_back(word);
	}
      for (auto &i : tab)
	std::cerr << i << std::endl;
      c.call(tab);
    }
  // cleanup the engine
  return 0;
}