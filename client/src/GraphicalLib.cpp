//
// Created by kyxo on 6/23/17.
//

#include "GraphicalLib.hpp"
#include "Client.hpp"

namespace 	Client
{
  GraphicalLib::GraphicalLib()
  {
    std::string s("fdp");
    this->_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1900, 1000), 0,
				      false, false, false, 0);
    this->_driver = this->_device->getVideoDriver();
    this->_smgr = this->_device->getSceneManager();
    this->_guienv = this->_device->getGUIEnvironment();
    _mesh[MESH::block] = _smgr->getMesh("./GFX/Models/cube.obj");
    mesh2 = _smgr->getMesh("./GFX/Models/cube.obj");
    text2 = _driver->getTexture("./GFX/groundGrass.png");
    irr::video::ITexture *text = _driver->getTexture("./GFX/groundGrass.png");
    irr::core::stringw wStr("fdp");
    this->_device->setWindowCaption(wStr.c_str());
    this->_device->getCursorControl()->setVisible(false);
  }

  GraphicalLib::~GraphicalLib()
  {
  }

  int GraphicalLib::addNode(const Vector3d &pos, GraphicalLib::MESH mesh, GraphicalLib::TEXT text)
  {
    irr::scene::IMeshSceneNode *node;

//    _node[_id] = _smgr->addOctreeSceneNode(mesh2->getMesh(0), 0, 1);  //_mesh[mesh]->getMesh(0), 0, 1);
//    _node[_id]->setPosition({pos.getX() * Client::SCALE, pos.getY() * Client::SCALE, 0});
//    if (text != TEXT::none)
//    _node[_id]->setMaterialTexture(0, text2);
//    _node[_id]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
//    _node[_id]->setScale({Client::SCALE, Client::SCALE, Client::SCALE});
    node = _smgr->addOctreeSceneNode(mesh2->getMesh(0), 0, 1);  //_mesh[mesh]->getMesh(0), 0, 1);
    node->setPosition({pos.getX() * Client::SCALE, pos.getY() * Client::SCALE, 0});
//    if (text != TEXT::none)
      node->setMaterialTexture(0, text2);
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    node->setScale({Client::SCALE, Client::SCALE, Client::SCALE});
    _id++;
    irr::scene::ICameraSceneNode *cam = _smgr->addCameraSceneNodeFPS();
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
    this->_driver->beginScene(true, true);
    _smgr->drawAll();
    _guienv->drawAll();
    this->_driver->endScene();
  }

}