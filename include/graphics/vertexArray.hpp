#pragma once
#include "vertexBuffer.hpp"
#include <GL/glew.h>

class VertexArray {
public:
  GLuint id;
  VertexArray() : id(0){};
  ~VertexArray() { glDeleteVertexArrays(1, &id); }

  bool is_initialize() { return id != 0; }

  void init() { glGenVertexArrays(1, &id); }

  void bind() {
    if (is_initialize()) {
      glBindVertexArray(id);
    }
  }
  void unbind() { glBindVertexArray(0); }
  void linkBuffer(VertexBuffer buffer, GLuint layout) {}
};
