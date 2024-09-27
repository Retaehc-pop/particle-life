#include "positionSetter.hpp"
#include <random>

PositionSetter::PositionSetter() : index(0) {
  setters = {[](Vector2D<double> position, int type, int n_types) {
               std::random_device rd;  // Seed
               std::mt19937 gen(rd()); // Standard mersenne_twister_engine
               std::uniform_real_distribution<double> dis(0.0,
                                                          1.0); // Range [0,1)
               position = {dis(gen), dis(gen)};
             },
             [](Vector2D<double> position, int type, int n_types) {},
             [](Vector2D<double> position, int type, int n_types) {}};
}

position_set_function PositionSetter::get_active() { return setters[index]; }

void PositionSetter::set_active(int i) { index = i; }
void PositionSetter::set_function(int i, position_set_function func) {
  setters[i] = func;
};
