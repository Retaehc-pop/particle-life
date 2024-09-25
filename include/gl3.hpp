#pragma once

#include <string>

class Gl3 {
  void create_device_object();
  void create_shader();

public:
  Gl3();
  Gl3(const std::string glVersion);
};
