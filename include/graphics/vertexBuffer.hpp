#pragma once

#include <GL/glew.h>
#include <vector>

class VertexBuffer {
public:
  GLuint id;

  VertexBuffer();
  ~VertexBuffer();
  void bind();
  void unbind();
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
