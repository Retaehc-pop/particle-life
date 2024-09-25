#pragma once

#include "vector2d.hpp"

class Particle {
public:
  Vector2D<double> position;
  Vector2D<double> velocity;
  int type;
};
