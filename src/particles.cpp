#include "particle.hpp"

Particle::Particle() {}

Particle::Particle(Vector2D<double> position, int typ)
    : position(position), type(typ) {}
