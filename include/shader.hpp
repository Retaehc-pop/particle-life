#pragma once

#include "color.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

class Shader {
public:
  GLuint shader_program;
  GLuint pos_attribute_location;
  GLuint vel_attribute_location;
  GLuint typ_attribute_location;
  // float transform[16];

private:
  GLuint time_uniform_location;
  GLuint palette_uniform_location;
  // GLuint transform_uniform_location;
  GLuint camTopLeft_uniform_location;
  GLuint wrap_uniform_location;
  GLuint size_uniform_location;

public:
  Shader();
  Shader(std::string vertex, std::string geometry, std::string fragment);
  void use();
  void set_time(float value);
  void set_palette(std::vector<Color> paletts);
  void set_size(float size);
  // void set_transform();
  void set_camTopLeft(float camLeft, float camTop);
  void set_wrap(bool wrap);
};
