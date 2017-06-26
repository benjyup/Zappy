//
// Created by vincent on 28/03/17.
//

#include "Vector3d.hpp"

Vector3d::Vector3d(int32_t x, int32_t y)
	: _x(x), _y(y)
{}

Vector3d::Vector3d(Vector3d const &other)
	: _x(other.getX()), _y(other.getY())
{}

Vector3d::~Vector3d(void)
{};

Vector3d &Vector3d::operator=(Vector3d const &other)
{
  if (&other != this)
    {
      this->_x = other.getX();
      this->_y = other.getY();
    }
  return (*this);
}

int32_t Vector3d::getX(void) const
{ return (this->_x); };

int32_t Vector3d::getY(void) const
{ return (this->_y); };

void Vector3d::setX(int32_t x)
{ this->_x = x; };

void Vector3d::setY(int32_t y)
{ this->_y = y; };

void Vector3d::setAll(int32_t x,int32_t y)
{this->_x = x; this->_y = y;}

bool Vector3d::operator==(Vector3d const &other) const
{
  return (this->getX() == other.getX() && this->getY() == other.getY());
}

bool Vector3d::operator<(Vector3d const &other) const
{
  return this->_x + this->_y > other._x + other._y;
}

bool Vector3d::operator>(Vector3d const &other) const
{
  return this->_x + this->_y < other._x + other._y;
}

Vector3d Vector3d::operator+(Vector3d const &other) const
{
  return (Vector3d(this->getX() + other.getX(), this->getY() + other.getY()));
}

bool Vector3d::operator!=(Vector3d const &other) const
{
  return !(_x == other._x && _y == other._y);
}

std::ostream		&operator<<(std::ostream &os, const Vector3d &vector)
{
  os << "x = " << vector.getX() << " y = " << vector.getY();
  return (os);
}
