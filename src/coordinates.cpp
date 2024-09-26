#include "coordinates.hpp"

Coordinates::Coordinates(double windowW, double windowH,
                         Vector2D<double> camPos, double camSize)
    : window_width(windowW), window_height(windowH), cam_pos(camPos),
      cam_size(camSize) {}

Vector2D<double> Coordinates::screen(Vector2D<double> world) {
  world -= cam_pos;
  world /= cam_size;

  if (window_width > window_height) {
    world.x *= window_height / window_width;
  } else {
    world.y *= window_width / window_height;
  }

  world.x += 0.5;
  world.y += 0.5;
  world.x *= window_width;
  world.y *= window_height;

  return world;
}
