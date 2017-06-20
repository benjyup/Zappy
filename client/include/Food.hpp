//
// Created by peixot_b on 20/06/17.
//

#ifndef CLIENT_GRAPH_FOOD_HPP
#define CLIENT_GRAPH_FOOD_HPP


class Food
{
 public:
  Food(Vector3d const &pos);

  virtual ~Food();
  void			eat();

  const Vector3d &get_pos() const;
  uint8_t get_apple() const;

  void set_pos(const Vector3d &_pos);
  void set_apple(uint8_t _apple);

 private:
  Vector3d		_pos;
  uint8_t 		_apple;
};


#endif //CLIENT_GRAPH_FOOD_HPP
