// #include "application.hpp"
#include "graphics.hpp"
#include "physics.hpp"
#include "shader.hpp"
#include "snapshot.hpp"

#include "setting/appSettings.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#define SETTINGS_FILE "setting..."

const std::string window_name = "Particle Life";

AppSetting app_setting;
GLFWwindow *window;
Graphics graphics;
Physics physics;
Snapshot snapshot;
Shader shader;

void glfw_error_callback(int error, const char *desc) {
  std::cerr << "GLFW [ERR] " << error << " :" << desc << std::endl;
}

void init(std::string title) {
  glfwSetErrorCallback(glfw_error_callback);

  if (!glfwInit()) {
    std::cerr << "[ERROR] Failed to initialize GLFW" << std::endl;
    exit(-1);
  }

  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // GLFW Major version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // GLFW Major version
  glfwWindowHint(GLFW_OPENGL_PROFILE,
                 GLFW_OPENGL_CORE_PROFILE); // use core profile

  window = glfwCreateWindow(800, 800, title.c_str(), NULL, NULL);
  if (window == NULL) {
    std::cerr << "[ERROR] Failed to create window" << std::endl;
    exit(-1);
  }
  glfwMakeContextCurrent(window);

  glfwSetFramebufferSizeCallback(window,
                                 [](GLFWwindow *window, int width, int height) {
                                   glViewport(0, 0, width, height);
                                 });
  glfwSwapInterval(1); // v-sync
}

void setup_graphics() { graphics.init(); }

void setup_physics() { physics.set_particle_count(100); }

void draw(double deltaTime) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  snapshot.set(physics);
  graphics.create_buffer_particle(graphics.shader, snapshot);

  graphics.shader.use();
  graphics.shader.set_time(deltaTime);
  graphics.shader.set_wrap(physics.settings.wrap);
  graphics.shader.set_size(app_setting.particle_size);

  glDisable(GL_SCISSOR_TEST);
  graphics.render();
}

void launch() {
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    exit(-1);
  }
  // glEnable(GL_MULTISAMPLE); // enable multisampling , improve image quality
  setup_graphics();
  setup_physics();
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  while (!glfwWindowShouldClose(window)) {

    draw(0); // deltaTime;

    glfwSwapBuffers(window); // swap the color buffers
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  // Terminate GLFW and free the error callback
  glfwTerminate();
}

int main() {
  // setting.load_config(SETTINGS_FILE);
  init("Particle Life");
  launch();
  return 0;
}
