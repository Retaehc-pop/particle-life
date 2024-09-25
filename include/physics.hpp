#pragma once
#include "particle.hpp"
#include "setting/physicsSettings.hpp"
#include "vector2d.hpp"
#include <vector>

class Physics {
private:
  PhysicsSetting settings;
  std::vector<Particle> particles_buffer;
  Vector2D<double> accelerate(double force, Vector2D<double> position);

public:
  std::vector<Particle> particles;
  void update_velocity(int index);
  void update_position(int index);
};
