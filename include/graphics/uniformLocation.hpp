#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class UniformLocation {
public:
  GLuint id;
  UniformLocation();
  UniformLocation(std::string name);
  UniformLocation(int program, std::string name);
};
