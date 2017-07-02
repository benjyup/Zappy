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

  Eggs(Vector3d const &pos, int father, int num, int id);

  Eggs();

  virtual ~Eggs();

  const Vector3d &get_pos() const;
  int get_id() const;

  void set_id(int _id);
  void 			set_pos(const Vector3d &_pos);
  void			eclosion();
  void			die();

 private:
  Vector3d		_pos;
  EGGSSTATE		_state;
  int 			_father;
  int 			_num;
  int 			_id;
};

#endif //CLIENT_GRAPH_EGGS_HPP
