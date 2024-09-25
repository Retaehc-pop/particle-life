#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class UniformLocation {
public:
  GLuint id;
  UniformLocation() : id(0){};
  UniformLocation(int program, std::string name) {
    id = glGetUniformLocation(program, name.c_str());
  };
};
