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

#include <vector>
#include "Client.hpp"

int             main(int ac, char **av) {

  std::string	s;
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
  s = av[1];
  if (ac == 1 && s.compare("-help"))
    {
      std::cerr << "USAGE: " << av[0] << " -p port -n name -h machine" << std::endl;
      std::cerr << "         port	is the port number" << std::endl;
      std::cerr << "         name	is the name of the team" << std::endl;
      std::cerr << "	     machine	is the name of the machine; localhost by default" << std::endl;
      return 0;
    }
  if (ac != 6)
    {
      std::cerr << "USAGE: " << av[0] << " -p port -n name -h machine" << std::endl;
      return 0;
    }

  // cleanup the engine
  return 0;
}