#include "snapshot.hpp"
#include <omp.h>

Snapshot::Snapshot(Physics p) : physics(p) {
  // create a physical frame at the time;

  positions.resize(p.particles.size() * 2);
  velocities.resize(p.particles.size() * 2);
  types.resize(p.particles.size());

#pragma omp parallel
  {
    for (auto i = 0; i < p.particles.size(); i++) {
      auto particle = p.particles[i];
      auto pos = 2 * i;

      positions[pos] = particle.position.x;
      positions[pos + 1] = particle.position.y;

      velocities[pos] = particle.velocity.x;
      velocities[pos + 1] = particle.velocity.y;

      types[i] = particle.type;
    }
  }
}
