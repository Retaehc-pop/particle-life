#pragma once

#include "renderer.hpp"
#include "setting/appSettings.hpp"
#include "threadController.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Application {
  GLFWwindow *window;
  GLFWmonitor *primary_monitor;
  GLFWvidmode *video_mode;
  int window_width;
  int window_height;
  int window_pos_X;
  int window_pos_Y;

  double mouse_X = -1;
  double mouse_Y = -1;
  double pmouse_X;
  double pmouse_Y;

  AppSetting settings;
  Physics physics;
  Renderer particle_renderer;
  Snapshot snapshot;
  ThreadController physics_thread;

public:
  Application(std::string title, bool fullscreen);
  void launch();
  void setup();
  void clear_screen();
  void render(double deltaTime);
  void update_canvas();
};
