//
// Created by kyxo on 6/23/17.
//

#include "GraphicalLib.hpp"
#include "Client.hpp"
#include "../irrlicht-1.8.4/include/irrlicht.h"

namespace 	Client
{
  GraphicalLib::GraphicalLib()
  {
    this->_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1900, 1000));
    this->_driver = this->_device->getVideoDriver();
    this->_smgr = this->_device->getSceneManager();
    this->_guienv = this->_device->getGUIEnvironment();
    _mesh[MESH::block] = _smgr->getMesh("./GFX/Models/cube.obj");
    _text[TEXT::grass] = _driver->getTexture("./GFX/groundGrass.png");
//    mesh2 = _smgr->getMesh("./GFX/Models/cube.obj");
//    text2 = _driver->getTexture("./GFX/groundGrass.png");
    irr::core::stringw wStr("fdp");
    this->_device->setWindowCaption(wStr.c_str());
    this->_device->getCursorControl()->setVisible(true);
    this->_smgr->addCameraSceneNodeFPS();
  }

  GraphicalLib::~GraphicalLib()
  {
  }


  int GraphicalLib::addNode(const Vector3d &pos, GraphicalLib::MESH mesh, GraphicalLib::TEXT text)
  {
    _node[_id] = _smgr->addOctreeSceneNode(_mesh[mesh]->getMesh(0), 0, 1);
    _node[_id]->setPosition({pos.getX() * Client::SCALE, 0, pos.getY() * Client::SCALE});
    if (text != TEXT::none)
      _node[_id]->setMaterialTexture(0, _text[text]);
    _node[_id]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node[_id]->setScale({Client::SCALE, Client::SCALE, Client::SCALE});
    _id++;
    std::cerr << "adding Node" << std::endl;
    return _id - 1;
  }

  void GraphicalLib::delNode(int id)
  {
    if (_node[id] == NULL)
      return ;
    _smgr->addToDeletionQueue(_node[id]);
    _node[_id] = nullptr;
  }

  void GraphicalLib::update()
  {
    this->_driver->beginScene();
    _smgr->drawAll();
    this->_driver->endScene();
  }

  bool GraphicalLib::is_running() const
  {
    return _device->run();
  }

}