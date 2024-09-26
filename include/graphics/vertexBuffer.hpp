#pragma once

#include <GL/glew.h>
#include <vector>

class VertexBuffer {
public:
  GLuint id;

  VertexBuffer() : id(0) {}
  void init() { glGenBuffers(1, &id); }
  ~VertexBuffer() { glDeleteBuffers(1, &id); }
  void bind() { glBindBuffer(GL_ARRAY_BUFFER, id); }
  void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
  template <typename T> void buffer_data(std::vector<T> data) {
    T arr[data.size()];
    std::copy(data.begin(), data.end(), arr);
    glBufferData(GL_ARRAY_BUFFER, data.size(), arr, GL_DYNAMIC_DRAW);
  }
  template <typename T> void buffer_subdata(std::vector<T> data) {
    T arr[data.size()];
    std::copy(data.begin(), data.end(), arr);
    glBufferSubData(GL_ARRAY_BUFFER, 0, data.size(), arr);
  }
};
