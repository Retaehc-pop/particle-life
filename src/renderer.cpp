#include "renderer.hpp"

Renderer::Renderer()
    : vao(), vbo_pos(), vbo_vel(), vbo_typ(), shader(), last_shader(-1),
      last_size(0) {}

void Renderer::init() {
  vao.init();
  vbo_pos.init();
  vbo_vel.init();
  vbo_typ.init();
  shader.init();
}

void Renderer::create_buffer_particle(Snapshot snapshot) {
  vao.bind();

  bool shader_changed = shader.id != last_shader;
  bool size_changed = snapshot.types.size() != last_size;
  last_shader = shader.id;
  last_size = snapshot.types.size();

  if (shader_changed) {
    if (shader.position_al.id != -1) {
      vbo_pos.bind();
      glVertexAttribPointer(shader.position_al.id, 3, GL_DOUBLE, false, 0, 0);
      glEnableVertexAttribArray(shader.position_al.id);
    }
    if (shader.velocity_al.id != -1) {
      vbo_vel.bind();
      glVertexAttribPointer(shader.velocity_al.id, 3, GL_DOUBLE, false, 0, 0);
      glEnableVertexAttribArray(shader.velocity_al.id);
    }
    if (shader.type_al.id != -1) {
      vbo_typ.bind();
      glVertexAttribIPointer(shader.type_al.id, 1, GL_INT, 0, 0);
      glEnableVertexAttribArray(shader.type_al.id);
    }
  }

  if (shader.position_al.id != -1) {
    vbo_pos.bind();
    if (size_changed || shader_changed) {
      vbo_pos.buffer_data(snapshot.positions);
    } else {
      vbo_pos.buffer_subdata(snapshot.positions);
    }
  }
  if (shader.velocity_al.id != -1) {
    vbo_vel.bind();
    if (size_changed || shader_changed) {
      vbo_vel.buffer_data(snapshot.velocities);
    } else {
      vbo_vel.buffer_subdata(snapshot.velocities);
    }
  }
  if (shader.type_al.id != -1) {
    vbo_typ.bind();
    if (size_changed || shader_changed) {
      vbo_typ.buffer_data(snapshot.types);
    } else {
      vbo_typ.buffer_subdata(snapshot.types);
    }
  }
}

void Renderer::render(int vp_width, int vp_height) {
  if (shader.id == 0 || last_size <= 0)
    std::cerr << shader.id << " " << last_size << std::endl;
  return;

  glDisable(GL_SCISSOR_TEST);
  glViewport(0, 0, vp_width, vp_height);
  shader.activate();
  vao.bind();
  glDrawArrays(GL_POINTS, 0, last_size);
}
