//
// Created by kyxo on 6/23/17.
//

#ifndef CLIENT_GRAPH_GRAPHICALLIB_HPP
#define CLIENT_GRAPH_GRAPHICALLIB_HPP

#include <unordered_map>
#include <map>
#include "irrlicht.h"
#include "Vector3d.hpp"

namespace  Client
{
  class GraphicalLib
  {
   public:
    enum class MESH : uint8_t
    {
      block = 0
    };

    enum class TEXT : uint8_t
    {
      none = 0,
      grass
    };

    GraphicalLib();
    virtual ~GraphicalLib();

    int		addNode(Vector3d const &pos, MESH mesh, TEXT);
    void	delNode(int id);
    void	update();

    irr::scene::ISceneManager			*_smgr;
   private:
    irr::IrrlichtDevice				*_device;
    irr::video::IVideoDriver			*_driver;
    irr::gui::IGUIEnvironment           	*_guienv;
    irr::scene::IAnimatedMesh 			*_cube;
    std::unordered_map<int, irr::scene::IMeshSceneNode *>	_node;
    std::map<MESH, irr::scene::IAnimatedMesh *> _mesh;
    std::map<TEXT, irr::video::ITexture *>	_text;
    int 						_id;
    irr::scene::IAnimatedMesh *mesh2;
    irr::video::ITexture	*text2;
  };
}

#endif //CLIENT_GRAPH_GRAPHICALLIB_HPP
