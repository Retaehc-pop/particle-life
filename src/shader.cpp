#include "shader.hpp"
#include "color.hpp"
#include <iostream>
#include <string>
#include <vector>

int make_shader_obj(std::string resource, int type, std::string name) {

  const char *src = resource.c_str();
  int shader_obj = glCreateShader(type);
  glShaderSource(shader_obj, 1, &src, nullptr);
  glCompileShader(shader_obj);

  int success;
  glGetShaderiv(shader_obj, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shader_obj, 512, NULL, infoLog);
    std::cerr << "Error compiling shader: " << name << std::endl;
    std::cerr << infoLog << std::endl;
  }
  // std::cout << shader_obj << std::endl;
  return shader_obj;
}

Shader::Shader(){};

Shader::Shader(std::string vertex, std::string geometry, std::string fragment) {
  shader_program = glCreateProgram();
  glAttachShader(shader_program,
                 make_shader_obj(vertex, GL_VERTEX_SHADER, "vertex"));
  glAttachShader(shader_program,
                 make_shader_obj(fragment, GL_FRAGMENT_SHADER, "fragment"));
  if (!geometry.empty()) {
    glAttachShader(shader_program,
                   make_shader_obj(geometry, GL_GEOMETRY_SHADER, "geometry"));
  }
  glLinkProgram(shader_program);

  int success;
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
    std::cerr << "Error linking shader program" << std::endl;
    std::cerr << infoLog << std::endl;
  }

  time_uniform_location = glGetUniformLocation(shader_program, "time");
  palette_uniform_location = glGetUniformLocation(shader_program, "palette");
  camTopLeft_uniform_location =
      glGetUniformLocation(shader_program, "camTopLeft");
  wrap_uniform_location = glGetUniformLocation(shader_program, "wrap");
  size_uniform_location = glGetUniformLocation(shader_program, "size");

  pos_attribute_location = glGetAttribLocation(shader_program, "pos");
  vel_attribute_location = glGetAttribLocation(shader_program, "vel");
  typ_attribute_location = glGetAttribLocation(shader_program, "typ");
}

void Shader::use() { glUseProgram(shader_program); }

void Shader::set_time(float value) {
  glUniform1f(time_uniform_location, value);
}

void Shader::set_palette(std::vector<Color> palette) {
  std::vector<float> colorArray;
  for (auto &col : palette) {
    colorArray.push_back(col.r);
    colorArray.push_back(col.g);
    colorArray.push_back(col.b);
    colorArray.push_back(col.a);
  }

  glUniform4fv(palette_uniform_location, palette.size(), colorArray.data());
}
void Shader::set_size(float size) { glUniform1f(size_uniform_location, size); }
// void Shader::set_transform(const Matrix4d &matrix) {
//   glUniformMatrix4fv(transform_uniform_location, 1, GL_FALSE,
//                      matrix.get(transform));
// }
void Shader::set_camTopLeft(float camLeft, float camTop) {
  glUniform2f(camTopLeft_uniform_location, camLeft, camTop);
}
void Shader::set_wrap(bool wrap) { glUniform1i(wrap_uniform_location, wrap); }
