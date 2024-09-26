#include "typeSetter.hpp"
#include <random>

int constrain(int value, int nTypes) {
  return std::max(0, std::min(nTypes - 1, value));
}

int map_type(double value, int nTypes) {
  return constrain(static_cast<int>(std::floor(value * nTypes)), nTypes);
}

TypeSetter::TypeSetter() : index(0) {
  setters = {
      [](Vector2D<double> position, Vector2D<double> velocity, int type,
         int n_types) {
        std::random_device rd;  // Seed
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine
        std::uniform_real_distribution<double> dis(0.0, 1.0); // Range [0,1)
        return static_cast<int>(std::floor(dis(gen) * n_types));
      },
      [](Vector2D<double> position, Vector2D<double> velocity, int type,
         int n_types) { return map_type(position.x, n_types); },
  };
};

type_set_function TypeSetter::get_active() { return setters[index]; }

void TypeSetter::set_active(int i) { index = i; }

void TypeSetter::set_function(int i, type_set_function func) {
  setters[i] = func;
}
