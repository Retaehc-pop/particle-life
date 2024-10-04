#pragma once

#include "shader.hpp"
#include "snapshot.hpp"
#include <GL/glew.h>

class Graphics {
public:
  Shader shader;

private:
  GLuint vao;
  GLuint vbo_pos;
  GLuint vbo_vel;
  GLuint vbo_typ;
  GLuint last_shader;
  size_t last_buffer_size;

public:
  Graphics();
  void init();
  void create_buffer_particle(Shader particle_shader, Snapshot snapshot);
  void render();
};
