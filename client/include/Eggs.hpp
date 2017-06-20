//
// Created by peixot_b on 20/06/17.
//

#ifndef CLIENT_GRAPH_EGGS_HPP
#define CLIENT_GRAPH_EGGS_HPP


class Eggs
{
 public:
  Eggs(Vector3d const &pos);

  virtual ~Eggs();

  const Vector3d &get_pos() const;

  void 			set_pos(const Vector3d &_pos);
  void			eclosion();

 private:
  Vector3d		_pos;
};


#endif //CLIENT_GRAPH_EGGS_HPP
