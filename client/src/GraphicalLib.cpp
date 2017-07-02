//
// Created by kyxo on 6/23/17.
//

#include "GraphicalLib.hpp"
#include "Client.hpp"

namespace 	Client
{
  GraphicalLib::GraphicalLib() : _id(0), _idAnims(1), _y(200)
  {
    this->_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1900, 1000));
    this->_driver = this->_device->getVideoDriver();
    this->_smgr = this->_device->getSceneManager();
    this->_guienv = this->_device->getGUIEnvironment();
    initMesh();
    irr::core::stringw wStr("ZapPyramide");
    this->_device->setWindowCaption(wStr.c_str());
    this->_device->getCursorControl()->setVisible(true);
    this->_smgr->addCameraSceneNodeFPS()->setPosition({Client::SCALE * 10, 40, 0});
    initDeco();
    initText();
  }

  void GraphicalLib::initMesh()
  {
    _mesh[MESH::block] = _smgr->getMesh("./GFX/Models/cube.obj");
    _mesh[MESH::minerals] = _smgr->getMesh("./GFX/Models/mineralshigh.obj");
    _text[TEXT::minerals1] = _driver->getTexture("./GFX/purpletext.png");
    _text[TEXT::minerals2] = _driver->getTexture("./GFX/redtext.png");
    _text[TEXT::minerals3] = _driver->getTexture("./GFX/greentext.png");
    _mesh[MESH::rock] = _smgr->getMesh("./GFX/Models/socle.obj");
    _text[TEXT::rock] = _driver->getTexture("./GFX/graytext.png");
    _mesh[MESH::character] = _smgr->getMesh("./GFX/ninja.b3d");
    _mesh[MESH::eggs] = _smgr->getMesh("./GFX/Models/eggs.obj");
    _text[TEXT::grass] = _driver->getTexture("./GFX/sandtext.jpg");
    _text[TEXT::eggs1] = _driver->getTexture("./GFX/redtext.png");
    _text[TEXT::sky] = _driver->getTexture("./GFX/sky.jpg");
    _text[TEXT::desert] = _driver->getTexture("./GFX/desert.jpg");
    _text[TEXT::stone] = _driver->getTexture("./GFX/stones.jpg");
    _text[TEXT::water] = _driver->getTexture("./GFX/water.jpg");
    _text[TEXT::ninja1] = _driver->getTexture("./GFX/nskinbl.jpg");
    _text[TEXT::ninja2] = _driver->getTexture("./GFX/nskinbr.jpg");
    _text[TEXT::ninja3] = _driver->getTexture("./GFX/nskingr.jpg");
    _text[TEXT::ninja4] = _driver->getTexture("./GFX/nskinrd.jpg");
    _text[TEXT::ninja5] = _driver->getTexture("./GFX/nskinwh.jpg");
  }

  void GraphicalLib::initDeco()
  {
    _smgr->addSkyDomeSceneNode(_text[TEXT::sky], 16, 16, 1.0f, 1.0f);
    _smgr->addSkyDomeSceneNode(_text[TEXT::desert], 16, 16, 1.0f, 1.0f)->setRotation({0, 0, -180});
    _smgr->setAmbientLight(irr::video::SColorf(0.7,0.7,0.7,1));
    irr::scene::IAnimatedMesh* plane = _smgr->addHillPlaneMesh("plane",
							       irr::core::dimension2d<irr::f32>(20,20),
							       irr::core::dimension2d<irr::u32>(200,200), 0, 0,
							       irr::core::dimension2d<irr::f32>(0,0),
							       irr::core::dimension2d<irr::f32>(100,100));
    irr::scene::ISceneNode* sea = _smgr->addWaterSurfaceSceneNode(plane->getMesh(0), 5.0f, 300.0f, 40.0f);
    sea->setMaterialTexture(0, _text[TEXT::stone]);
    sea->setPosition({0 + (Client::SCALE * 10 / 2), 5, 0 + (Client::SCALE * 10 / 2)});
    sea->setMaterialTexture(1, _text[TEXT::water]);
    sea->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    sea->setMaterialType(irr::video::EMT_REFLECTION_2_LAYER);
  }

  void GraphicalLib::initText()
  {
    this->_gui = this->_device->getGUIEnvironment();;
    if (_gui != NULL)
      this->_font = _gui->getFont("./GFX/font_space.bmp");
    _size = _font->getDimension(L"Test Text");
    _text2 = "Bienvenue sur le mode Spectateur !";
    _driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
    _driver->getMaterial2D().AntiAliasing = irr::video::EAAM_FULL_BASIC;
    _images = _driver->getTexture("./GFX/prompt.png");
    _driver->makeColorKeyTexture(_images, irr::core::position2d<irr::s32>(0,0));
  }

  void GraphicalLib::set_text2(const irr::core::stringw &_text2, bool newLine)
  {
    if (newLine)
      _y -= _size.Height;
    GraphicalLib::_text2 += _text2;
  }

  GraphicalLib::~GraphicalLib()
  {
  }

  int GraphicalLib::addNode(const Vector3d &pos, GraphicalLib::MESH mesh,
			    GraphicalLib::TEXT text, irr::f32 Scale, int alt)
  {
    _node[_id] = _smgr->addAnimatedMeshSceneNode(_mesh[mesh]);
    if (mesh == MESH::minerals || mesh == MESH::rock)
      _node[_id]->setPosition({(float)(pos.getX() * Client::SCALE - Client::SCALE / 2),
			       (float)(alt * Client::SCALE), (float)(pos.getY() * Client::SCALE + Client::SCALE / 2)});
    else
      _node[_id]->setPosition({(float)(pos.getX() * Client::SCALE), (float)(alt * Client::SCALE),
			       (float)(pos.getY() * Client::SCALE)});
    if (text != TEXT::none)
      _node[_id]->setMaterialTexture(0, _text[text]);
    _node[_id]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node[_id]->setScale({Scale, Scale, Scale});
    _id++;
    return _id - 1;
  }

  int GraphicalLib::addCharacterNode(const irr::core::vector3df &pos, int team,
				     irr::f32 Scale, int dir)
  {
    _node[_id] = _smgr->addAnimatedMeshSceneNode(_mesh[MESH::character]);
    _node[_id]->setPosition(pos);
    _node[_id]->setMaterialTexture(0, _text[(GraphicalLib::TEXT)((int)GraphicalLib::TEXT::ninja1 + team % 5)]);
    _node[_id]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node[_id]->setScale({Scale, Scale, Scale});
    _node[_id]->setFrameLoop(205, 249);
    _node[_id]->setAnimationSpeed(10);
    _node[_id]->setRotation({0, (float)(dir * 90 - 90), 0});
    _id++;
    return _id - 1;
  }

  int GraphicalLib::addEggsNode(irr::core::vector3df const &pos)
  {
    _node[_id] = _smgr->addAnimatedMeshSceneNode(_mesh[MESH::eggs]);
    _node[_id]->setPosition(pos);
    _node[_id]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _node[_id]->setScale({1, 1, 1});
    _node[_id]->setMaterialTexture(0, _text[TEXT::eggs1]);
    _id++;
    return _id - 1;
  }

  void GraphicalLib::delNode(int id)
  {
    if (_node[id] == nullptr)
      return ;
    _node[id]->remove();
    _node[_id] = nullptr;
  }

  void GraphicalLib::update()
  {
    this->_driver->beginScene();
    _smgr->drawAll();
    _driver->draw2DImage(_images, irr::core::position2d<irr::s32>(5, 0),
			 irr::core::rect<irr::s32>(0,0,342,215), 0,
			 irr::video::SColor(100,255,255,255), false);
    _font->draw(_text2, irr::core::rect<irr::s32>(20, _y, (20 + _size.Width),(668 + _size.Height)),
		irr::video::SColor(255,255,255,255));

    this->_driver->endScene();
  }

  bool GraphicalLib::is_running() const
  {
    return _device->run();
  }

  irr::core::vector3df const &GraphicalLib::getScale(int id)
  {
    return this->_node[id]->getScale();
  }

  void GraphicalLib::set_scale(irr::f32 scale, int id)
  {
    _node[id]->setScale({scale, scale, scale});
  }

  irr::core::vector3df const &GraphicalLib::getPos(int id)
  {
    return _node[id]->getPosition();
  }

  int	GraphicalLib::addFlyStraightAnimator(int id, irr::core::vector3df const &from,
						  irr::core::vector3df const &to, int speed, int dir)
  {
    _anims[_idAnims] = _smgr->createFlyStraightAnimator(from, to, (irr::u32)speed, false);
    _node[id]->addAnimator(_anims[_idAnims]);
    _node[id]->setRotation({0, (float)(dir * 90 - 90), 0});
    _idAnims++;
    _node[id]->setAnimationSpeed(18);
    _node[id]->setFrameLoop(15, 30);
    return (_idAnims - 1);
  }

  void GraphicalLib::addRotateAnimation(int id)
  {
    irr::core::vector3df	v;

    irr::scene::ISceneNodeAnimator *anim = _smgr->createRotationAnimator({0, 1, 0});
    _node[id]->addAnimator(anim);
    v = _node[id]->getPosition();
    _node[id]->setPosition({v.X, v.Y + 0.5f, v.Z});
    anim->drop();
  }

  bool GraphicalLib::isAnimationEnd(int id)
  {
    if (_anims[id]->hasFinished())
      {
	_anims[id]->drop();
	return true;
      }
    return false;
  }

  bool GraphicalLib::isAnimationEnd2(int id)
  {
    return _node[id]->getFrameNr() >= _node[id]->getEndFrame();
  }

  void GraphicalLib::idle(int id)
  {
    _node[id]->setLoopMode(true);
    _node[id]->setFrameLoop(204, 249);
    _node[id]->setAnimationSpeed(10);
  }

  void GraphicalLib::incantating(int id)
  {
    _node[id]->setLoopMode(true);
    _node[id]->setFrameLoop(59, 67);
    _node[id]->setAnimationSpeed(10);
  }

  void GraphicalLib::laying(int id)
  {
    _node[id]->setLoopMode(false);
    _node[id]->setFrameLoop(118, 122);
    _node[id]->setAnimationSpeed(7);
  }

  void GraphicalLib::taking(int id)
  {
    _node[id]->setLoopMode(false);
    _node[id]->setFrameLoop(83, 92);
    _node[id]->setAnimationSpeed(6);
  }

  void GraphicalLib::dying(int id)
  {
    _node[id]->setLoopMode(false);
    _node[id]->setFrameLoop(173, 181);
    _node[id]->setAnimationSpeed(3);
  }

  void GraphicalLib::uping(int id)
  {
    _node[id]->setLoopMode(false);
    _node[id]->setFrameLoop(145, 157);
    _node[id]->setAnimationSpeed(20);
  }

  void GraphicalLib::pushing(int id)
  {
    _node[id]->setLoopMode(false);
    _node[id]->setFrameLoop(72, 82);
    _node[id]->setAnimationSpeed(10);
  }
}