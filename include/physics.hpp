#pragma once
#include "particle.hpp"
#include "positionSetter.hpp"
#include "setting/physicsSettings.hpp"
#include "typeSetter.hpp"

#include "vector2d.hpp"
#include <vector>

class Physics {
private:
  PhysicsSetting settings;
  std::vector<Particle> particles_buffer;
  Vector2D<double> accelerate(double force, Vector2D<double> position);

  PositionSetter pos_setter;
  TypeSetter typ_setter;

public:
  Physics();
  std::vector<Particle> particles;
  void update_velocity(int index);
  void update_position(int index);
  void set_particle_count(int n);
};
