#pragma once
#include "vector2d.hpp"
#include <vector>

typedef void (*position_set_function)(Vector2D<double> &position, int type,
                                      int n_types);

class PositionSetter {
private:
  int index;
  std::vector<position_set_function> setters;

public:
  PositionSetter();
  position_set_function get_active();
  void set_active(int index);
  void set_function(int index, position_set_function func);
};
