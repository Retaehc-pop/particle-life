#include "graphics/vertexBuffer.hpp"
#include <vector>

VertexBuffer::VertexBuffer() { glGenBuffers(1, &id); }

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &id); }

void VertexBuffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, id); }

void VertexBuffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

template <typename T> void VertexBuffer::buffer_data(std::vector<T> x) {
  T arr[x.size()];
  std::copy(x.begin(), x.end(), arr);
  glBufferData(GL_ARRAY_BUFFER, x.size(), arr, GL_DYNAMIC_DRAW);
}
template <typename T> void VertexBuffer::buffer_subdata(std::vector<T> x) {
  T arr[x.size()];
  std::copy(x.begin(), x.end(), arr);
  glBufferSubData(GL_ARRAY_BUFFER, 0, x.size(), arr);
}
