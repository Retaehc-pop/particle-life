#pragma once
#include "graphics/shader.hpp"
#include "graphics/vertexArray.hpp"
#include "graphics/vertexBuffer.hpp"
#include "snapshot.hpp"

class Renderer {
private:
  VertexArray vao;
  VertexBuffer vbo_pos;
  VertexBuffer vbo_vel;
  VertexBuffer vbo_typ;
  GLuint last_shader;
  size_t last_size;

public:
  Shader shader;
  Renderer();
  void create_buffer_particle(Snapshot snapshot);
  void render(int vp_width, int vp_height);
  void init();
};
