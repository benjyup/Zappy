//
// Created by puente_t on 13/03/17.
//

#ifndef ARCADE_VECTOR3D_HPP
#define ARCADE_VECTOR3D_HPP

#include <cstdint>
#include <ostream>

  class Vector3d
  {
   private:
    int32_t _x;
    int32_t _y;
   public:
    Vector3d(int32_t x, int32_t y);

    Vector3d(Vector3d const &other);

    ~Vector3d(void);

    Vector3d &operator=(Vector3d const &other);

    int32_t getX(void) const;

    int32_t getY(void) const;

    void setX(int32_t x);

    void setY(int32_t y);

    void setAll(int32_t x,int32_t y);

    bool operator==(Vector3d const &other) const;

    bool operator<(Vector3d const &other) const;

    bool operator>(Vector3d const &other) const;

    bool operator!=(Vector3d const &other) const;

    Vector3d operator+(Vector3d const &other) const;
  };
 std::ostream		&operator<<(std::ostream &os, const Vector3d &vector);

#endif //ARCADE_VECTOR3D_HPP
