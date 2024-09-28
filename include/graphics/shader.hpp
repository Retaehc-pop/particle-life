#pragma once

#include "graphics/attributeLocation.hpp"
#include "graphics/uniformLocation.hpp"
#include <string>

class Shader {
private:
public:
  UniformLocation time_ul;
  UniformLocation transform_ul;
  UniformLocation palette_ul;
  UniformLocation size_ul;
  UniformLocation detail_ul;
  AttributeLocation position_al;
  AttributeLocation velocity_al;
  AttributeLocation type_al;

  GLuint id;
  Shader(std::string vertex, std::string geometry, std::string fragment);
  Shader();
  void init();
  void activate();
  void set_time(float time);
  void set_size(float size);
  void set_detail(int size);
  void set_transform(const float *matrix);
};
