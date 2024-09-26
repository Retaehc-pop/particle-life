#pragma once
#include "vector2d.hpp"
#include <vector>

typedef int (*type_set_function)(Vector2D<double> position,
                                 Vector2D<double> velocity, int type,
                                 int n_types);

class TypeSetter {
private:
  int index;
  std::vector<type_set_function> setters;
  // int constrain(int value, int n_types);
  // int map_type(double value, int n_types);

public:
  TypeSetter();
  type_set_function get_active();
  void set_active(int index);
  void set_function(int index, type_set_function func);
};
