#include "graphics/elementBuffer.hpp"
#include <GL/glew.h>

ElementBuffer::ElementBuffer(GLuint *indices, GLsizeiptr size) : id(0){};

void ElementBuffer::bind() {}

void ElementBuffer::unbind() {}
