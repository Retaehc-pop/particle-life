#include "physics.hpp"
#include "particle.hpp"
#include "vector2d.hpp"

void Physics::update_velocity(int i) {
  auto p = particles[i];
  double friction_factor;
  p.velocity *= friction_factor;

  auto start = 0;
  auto stop = 0;

  for (int j = start; j < stop; j++) {
    if (i == j)
      continue;
    auto q = particles[j];
    auto relative_distance = p.position - q.position;
    auto distance_magnitude = relative_distance.magnitude();
    if (distance_magnitude != 0 &&
        distance_magnitude <= settings.rmax * settings.rmax) {
      relative_distance /= settings.rmax;
      auto deltaVelocity =
          accelerate(settings.matrix.get(p.type, q.type), relative_distance);

      p.velocity +=
          (deltaVelocity * settings.rmax * settings.force * settings.deltaTime);
    }
  }
}

Vector2D<double> Physics::accelerate(double force,
                                     Vector2D<double> relative_distance) {
  if (false) {
  }
  return {0, 0};
}

void Physics::update_position(int i) {
  Particle p = particles[i];
  p.position += p.velocity * settings.deltaTime; // todo deltaTime instead of 2;
}
