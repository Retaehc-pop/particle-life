#pragma once

#include "vector2d.hpp"

class Particle {
public:
  Particle();
  Particle(Vector2D<double> position, int type);
  Vector2D<double> position;
  Vector2D<double> velocity;
  int type;
};
