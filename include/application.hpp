#pragma once

#include "renderer.hpp"
#include "setting/appSettings.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
class Application {
  AppSetting settings;
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

  Renderer particle_renderer;

public:
  Application(std::string title, AppSetting settings);
  void launch();
  void setup();
  void clear_screen();
  void render(double deltaTime);
  void update_canvas();
};
