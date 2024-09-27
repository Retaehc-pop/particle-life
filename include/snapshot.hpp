#pragma once

#include <particle.hpp>
#include <physics.hpp>

class Snapshot {
private:
  Physics physics;

public:
  Snapshot();
  Snapshot(Physics p);

  std::vector<int> types;
  std::vector<double> velocities;
  std::vector<double> positions;

  void set(Physics p);
};
