#pragma once

#include <GL/glew.h>

class ElementBuffer {
public:
  // ID reference of Elements Buffer Object
  GLuint id;
  // Constructor that generates a Elements Buffer Object and links it to indices
  ElementBuffer(GLuint *indices, GLsizeiptr size);

  // Binds the EBO
  void bind();
  // Unbinds the EBO
  void unbind();
};
