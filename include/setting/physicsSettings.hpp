#pragma once

#include "forceMatrix.hpp"

class PhysicsSetting {
public:
  bool wrap = false;
  double rmax = 0.2;
  double friction = 0.85;
  double force = 1.0f;
  double deltaTime = 0.02f;
  ForceMatrix matrix;

  PhysicsSetting() : matrix(5){};
  PhysicsSetting(bool wrap, double rmax, double friction, double dt,
                 double force, ForceMatrix matrix)
      : wrap(wrap), rmax(rmax), friction(friction), deltaTime(dt), force(force),
        matrix(matrix) {}

  PhysicsSetting deepCopy() {
    PhysicsSetting p = {wrap,      rmax,  friction,
                        deltaTime, force, matrix.deepCopy()};
    return p;
  }
};
