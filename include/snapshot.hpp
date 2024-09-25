#pragma once

#include <particle.hpp>
#include <physics.hpp>

class Snapshot {
private:
  Physics physics;

public:
  std::vector<int> types;
  std::vector<double> velocities;
  std::vector<double> positions;
  Snapshot(Physics p);
};
