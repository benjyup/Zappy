//
// Created by kyxo on 6/23/17.
//

#ifndef CLIENT_GRAPH_GRAPHICALLIB_HPP
#define CLIENT_GRAPH_GRAPHICALLIB_HPP

#include <unordered_map>
#include <map>
#include "Vector3d.hpp"
#include "irrlicht.h"

namespace  Client
{
  class GraphicalLib
  {
   public:
    enum class MESH : uint8_t
    {
      block = 0,
      minerals,
      character,
      eggs,
      rock
    };

    enum class TEXT : uint8_t
    {
      none = 0,
      grass,
      eggs1,
      minerals1,
      minerals2,
      minerals3,
      rock
    };

    GraphicalLib();
    virtual ~GraphicalLib();

    int		addNode(Vector3d const &pos, MESH mesh, TEXT, irr::f32 scale, int alt);
    int		addCharacterNode(irr::core::vector3df const &pos, TEXT, irr::f32 scale, int dir);
    int 	addEggsNode(irr::core::vector3df const &pos);

    void	delNode(int id);
    void	update();
    void	set_scale(irr::f32 scale, int id);
    bool 	isAnimationEnd(int id);
    bool 	isAnimationEnd2(int id);

    bool 	is_running() const;
    irr::core::vector3df const &getPos(int id);
    irr::core::vector3df const	&getScale(int id);
    int addFlyStraightAnimator(int id, irr::core::vector3df const &from,
			       irr::core::vector3df const &to, int speed, int dir);
    void	 addRotateAnimation(int id);

    void			idle(int id);
    void			incantating(int id);
    void			laying(int id);
    void			taking(int id);
    void			dying(int id);

   private:
    irr::IrrlichtDevice				*_device;
    irr::scene::ISceneManager			*_smgr;
    irr::video::IVideoDriver			*_driver;
    irr::gui::IGUIEnvironment           	*_guienv;
    irr::scene::IAnimatedMesh 			*_cube;
    std::unordered_map<int, irr::scene::IAnimatedMeshSceneNode *>	_node;
    std::map<MESH, irr::scene::IAnimatedMesh *> _mesh;
    std::map<TEXT, irr::video::ITexture *>	_text;
    int 						_id;
    std::unordered_map<int, irr::scene::ISceneNodeAnimator *>		_anims;
    int 								_idAnims;
  };
}

#endif //CLIENT_GRAPH_GRAPHICALLIB_HPP
