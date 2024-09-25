#include "graphics/shader.hpp"
#include "graphics/attributeLocation.hpp"
#include "graphics/uniformLocation.hpp"
#include <string>

int make_shader_obj(std::string resource, int type, std::string name) {
  std::string src = "";
  int shader_obj = glCreateShader(type);
  glCompileShader(shader_obj);
  // printShaderErrors(shader_obj,name.);
  return shader_obj;
}

Shader::Shader() : id(0) {}

Shader::Shader(std::string vertex, std::string geometry, std::string fragment)
    : id(0) {

  id = glCreateProgram();
  glAttachShader(id, make_shader_obj(vertex, GL_VERTEX_SHADER, "vertex"));
  if (geometry != "")
    glAttachShader(id,
                   make_shader_obj(geometry, GL_GEOMETRY_SHADER, "geometry"));
  glAttachShader(id, make_shader_obj(fragment, GL_FRAGMENT_SHADER, "fragment"));

  time_ul = UniformLocation(id, "time");
  transform_ul = UniformLocation(id, "transform");
  palette_ul = UniformLocation(id, "palette");
  size_ul = UniformLocation(id, "size");
  detail_ul = UniformLocation(id, "detail");
  position_al = AttributeLocation(id, "x");
  velocity_al = AttributeLocation(id, "v");
  type_al = AttributeLocation(id, "type");
}

void Shader::activate() { glUseProgram(id); }

void Shader::set_time(float t) { glUniform1f(time_ul.id, t); }

void Shader::set_size(float size) { glUniform1f(size_ul.id, size); }

void Shader::set_detail(int detail) { glUniform1i(detail_ul.id, detail); }

void Shader::set_transform(const float *matrix) {
  glUniformMatrix4fv(transform_ul.id, 1, GL_FALSE, NULL);
}
