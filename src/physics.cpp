#include "physics.hpp"
#include "particle.hpp"
#include "positionSetter.hpp"
#include "vector2d.hpp"

Physics::Physics() : settings(), typ_setter(), pos_setter(){};

void Physics::set_particle_types(Particle &p) {
  p.type = typ_setter.get_active()({}, {}, p.type, settings.matrix.size);
}

void Physics::set_particle_position(Particle &p) {
  pos_setter.get_active()(p.position, p.type, settings.matrix.size);
  // std::cout << "(" << p.position.x << "," << p.position.y << ")" <<
  // std::endl;
  p.velocity = {0, 0};
}

Particle Physics::generate_particle() {
  Particle p;
  set_particle_types(p);
  set_particle_position(p);
  return p;
}

void Physics::set_particle_count(int n) {
  particles.resize(n);
  for (int i = 0; i < n; i++) {
    particles[i] = generate_particle();
  }
}
void Physics::update_particles() {

  for (int i = 0; i < particles.size(); i++) {
    update_velocity(i);
  }

  for (int i = 0; i < particles.size(); i++) {
    update_position(i);
  }
}

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
