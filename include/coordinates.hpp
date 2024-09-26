#pragma once

#include "vector2d.hpp"

class Coordinates {
public:
  double window_width;
  double window_height;
  Vector2D<double> cam_pos;
  double cam_size;

  Coordinates(double windowW, double windowH, Vector2D<double> camPos,
              double camSize);
  Vector2D<double> screen(Vector2D<double> world);
  void apply();
};
