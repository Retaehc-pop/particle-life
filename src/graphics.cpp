#include "graphics.hpp"
#include "shader.hpp"
#include <GL/glext.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// complete
std::string get_resource(std::string filename) {
  std::ifstream shaderFile(filename);
  if (!shaderFile.is_open()) {
    std::cerr << "Failed to open shader file: " << filename << std::endl;
    return "";
  }
  std::stringstream shaderStream;
  shaderStream << shaderFile.rdbuf();
  shaderFile.close();
  return shaderStream.str();
}

Graphics::Graphics()
    : vao(), vbo_pos(), vbo_typ(), shader(), last_shader(-1),
      last_buffer_size(0) {}

void Graphics::init() {
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo_pos);
  glGenBuffers(1, &vbo_vel);
  glGenBuffers(1, &vbo_typ);
  shader = {
      get_resource("../resources/shaders/default.vert"),
      get_resource("../resources/shaders/default.geom"),
      get_resource("../resources/shaders/default.frag"),
  };

  // glBindVertexArray(vao);
  // glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
}

void Graphics::create_buffer_particle(Shader particle_shader,
                                      Snapshot snapshot) {

  glBindVertexArray(vao);

  shader.use();

  bool shader_changed = shader.shader_program != last_shader;
  bool size_changed = snapshot.types.size() != last_buffer_size;
  last_shader = shader.shader_program;
  last_buffer_size = snapshot.types.size();

  if (shader_changed) {
    if (particle_shader.pos_attribute_location != -1) {
      glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
      glVertexAttribPointer(shader.pos_attribute_location, 2, GL_DOUBLE, false,
                            0, 0);
      glEnableVertexAttribArray(shader.pos_attribute_location);
    }
    if (particle_shader.vel_attribute_location != -1) {
      glBindBuffer(GL_ARRAY_BUFFER, vbo_vel);
      glVertexAttribPointer(shader.vel_attribute_location, 2, GL_DOUBLE, false,
                            0, 0);
      glEnableVertexAttribArray(shader.vel_attribute_location);
    }
    if (particle_shader.typ_attribute_location != -1) {
      glBindBuffer(GL_ARRAY_BUFFER, vbo_typ);
      glVertexAttribIPointer(shader.typ_attribute_location, 1, GL_INT, 0, 0);
      glEnableVertexAttribArray(shader.typ_attribute_location);
    }
  }

  if (shader.pos_attribute_location != -1) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    if (size_changed || shader_changed) {
      glBufferData(GL_ARRAY_BUFFER,
                   snapshot.positions.size() * sizeof(Vector2D<double>),
                   snapshot.positions.data(), GL_DYNAMIC_COPY);
    } else {
      glBufferSubData(GL_ARRAY_BUFFER, 0,
                      snapshot.positions.size() * sizeof(Vector2D<double>),
                      snapshot.positions.data());
    }
  }
  if (shader.vel_attribute_location != -1) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vel);
    if (size_changed || shader_changed) {
      glBufferData(GL_ARRAY_BUFFER,
                   snapshot.velocities.size() * sizeof(Vector2D<double>),
                   snapshot.velocities.data(), GL_DYNAMIC_COPY);
    } else {
      glBufferSubData(GL_ARRAY_BUFFER, 0,
                      snapshot.velocities.size() * sizeof(Vector2D<double>),
                      snapshot.velocities.data());
    }
  }
  if (shader.typ_attribute_location != -1) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_typ);
    if (size_changed || shader_changed) {
      glBufferData(GL_ARRAY_BUFFER, snapshot.types.size() * sizeof(int),
                   snapshot.types.data(), GL_DYNAMIC_COPY);
    } else {
      glBufferSubData(GL_ARRAY_BUFFER, 0,
                      snapshot.velocities.size() * sizeof(int),
                      snapshot.types.data());
    }
  }
}

void Graphics::render() {
  if (last_buffer_size == 0) {
    std::cerr << shader.shader_program << " " << last_buffer_size << std::endl;
    return;
  }
  int vp_width = 800, vp_height = 600;   // Placeholder values, replace with
                                         // actual window size retrieval logic
  glViewport(0, 0, vp_width, vp_height); // Set the OpenGL viewport

  shader.use();           // Make sure the shader is active
  glBindVertexArray(vao); // Bind VAO
  glDrawArrays(GL_POINTS, 0, last_buffer_size);
}
