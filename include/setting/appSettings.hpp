#pragma once
#include <exception>
#include <string>
class AppSettingException : public std::exception {};

class AppSetting {
public:
  bool fullscreen = false;        // start in full screen
  double zoop_scale_factor = 1.2; // increase size by 1.2 every zoom
  float particle_size = 4.0f;     // particle in pixel
  bool particle_size_zoom_independent = false; // change particle zoom size
  double shift_smoothness = 0.3;               // change location smoothness
  double zoom_smoothness = 0.3;                // zoom smoothness
  double cam_movement_speed = 1.0;             // camera speed
  bool show_cursor = true;                     // cursor on screen
  double cursor_zize = 0.1;
  std::string cursor_action_left = "Move";
  std::string cursor_action_right = "Delete";
  int brush_power = 100;
  double matrix_gui_step_size = 0.2;
  std::string palette = "RainbowSmooth12.map"; // starting position
  std::string shader = "default";              // shader_name
  double dt = 0.02;                            // deltaTime step
  bool autoDt = true;                          // auso_deltaTime_step

  void load_config(std::string filename) {}
};
