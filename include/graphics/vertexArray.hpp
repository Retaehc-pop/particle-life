#pragma once
#include "vertexBuffer.hpp"
#include <GL/glew.h>

class VertexArray {
public:
  GLuint id;

  // constructor
  VertexArray();
  ~VertexArray();

  void bind();
  void unbind();
  void linkBuffer(VertexBuffer buffer, GLuint layout);
};
