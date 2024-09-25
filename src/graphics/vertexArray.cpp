#include "graphics/vertexArray.hpp"
#include "graphics/vertexBuffer.hpp"
#include <GLFW/glfw3.h>

VertexArray::VertexArray() { glGenVertexArrays(1, &id); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &id); }

void VertexArray::bind() { glBindVertexArray(id); }

void VertexArray::unbind() { glBindVertexArray(0); }

void VertexArray::linkBuffer(VertexBuffer buffer, GLuint layout) {}
