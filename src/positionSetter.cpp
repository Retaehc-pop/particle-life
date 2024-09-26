#pragma once
#include "positionSetter.hpp"

PositionSetter::PositionSetter() : index(0) {
  setters = {[](Vector2D<double> position, int type, int n_types) {},
             [](Vector2D<double> position, int type, int n_types) {},
             [](Vector2D<double> position, int type, int n_types) {}};
}

position_set_function PositionSetter::get_active() { return setters[index]; }

void PositionSetter::set_active(int i) { index = i; }
void PositionSetter::set_function(int i, position_set_function func) {
  setters[i] = func;
};
