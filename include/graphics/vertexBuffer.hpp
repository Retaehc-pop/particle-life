#pragma once

#include <GL/glew.h>
#include <vector>

class VertexBuffer {
public:
  GLuint id;
  VertexBuffer(GLfloat *vertices, GLsizeiptr size);
  VertexBuffer();
  ~VertexBuffer();
  void bind();
  void unbind();
  template <typename T> void buffer_data(std::vector<T> data);
  template <typename T> void buffer_subdata(std::vector<T> data);
};
