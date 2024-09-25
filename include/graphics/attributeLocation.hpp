#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class AttributeLocation {
public:
  GLuint id;
  AttributeLocation() : id(0){};
  AttributeLocation(int program, std::string name) {
    id = glGetAttribLocation(program, name.c_str());
  }
};
