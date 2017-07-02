//
// Created by peixot_b on 20/06/17.
//

#ifndef CLIENT_GRAPH_DRONE_HPP
#define CLIENT_GRAPH_DRONE_HPP


#include <cstdint>

class Drone
{
 public:
  enum class DIR : uint8_t
  {
    NORTH = 1,
    EAST,
    SOUTH,
    OUEST
  };

  Drone();

  virtual ~Drone();

  void 	flight(Drone::DIR direction);
};


#endif //CLIENT_GRAPH_DRONE_HPP
