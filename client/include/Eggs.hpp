//
// Created by peixot_b on 20/06/17.
//

#ifndef CLIENT_GRAPH_EGGS_HPP
#define CLIENT_GRAPH_EGGS_HPP


class Eggs
{
 public:

  enum class EGGSSTATE : uint8_t
  {
    close = 0,
    hatch,
    die
  };

  Eggs(Vector3d const &pos, int father);

  virtual ~Eggs();

  const Vector3d &get_pos() const;

  void 			set_pos(const Vector3d &_pos);
  void			eclosion();
  void			die();

 private:
  Vector3d		_pos;
  EGGSSTATE		_state;
  int 			_father;
};

#endif //CLIENT_GRAPH_EGGS_HPP
