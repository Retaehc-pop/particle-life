#include "application.hpp"
#include "clock.hpp"
#include "graphics/attributeLocation.hpp"
#include <GL/gl.h>
#include <chrono>
#include <iostream>

Application::Application(std::string title, AppSetting settings)
    : settings(settings) {
  if (!glfwInit()) {
    std::cerr << "[ERROR] Failed to initialize GLFW" << std::endl;
    exit(-1);
  }

  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);      // hide window after creation
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);     // resizeable window
  glfwWindowHint(GLFW_SAMPLES, 16);              // 16x MSAA
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // GLFW Major version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // GLFW Major version
  glfwWindowHint(GLFW_OPENGL_PROFILE,
                 GLFW_OPENGL_CORE_PROFILE); // use core profile
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

  GLFWmonitor *primary = glfwGetPrimaryMonitor();
  const GLFWvidmode *videoMode = glfwGetVideoMode(primary);

  if (videoMode == NULL) {
    std::cerr << "[ERROR] getVideoMode return null" << std::endl;
    exit(-1);
  }

  int monitor_width = videoMode->width;
  int monitor_height = videoMode->height;

  double f = 0.2;
  window_pos_X = (int)(f * monitor_width / 2);
  window_pos_Y = (int)(f * monitor_height / 2);
  window_width = (int)((1 - f) * monitor_width);
  window_height = (int)((1 - f) * monitor_height);

  if (settings.fullscreen) {
    window = glfwCreateWindow(window_width, window_height, title.c_str(),
                              primary, NULL);
  } else {
    window = glfwCreateWindow(window_width, window_height, title.c_str(), NULL,
                              NULL);
  }

  if (window == NULL) {
    std::cerr << "[ERROR] Failed to create window" << std::endl;
    exit(-1);
  }

  glfwMakeContextCurrent(window);
  // glfwSwapInterval(1);
  glfwShowWindow(window);
  glViewport(0, 0, 800, 800);
}

void Application::launch() {
  glewInit();
  glClearColor(0, 0, 0, 0);
  // setup();
  Clock guiClock;
  while (!glfwWindowShouldClose(window)) {
    guiClock.tick();

    pmouse_X = mouse_X;
    pmouse_Y = mouse_Y;

    glfwPollEvents();

    double deltaTime = guiClock.get_deltaTime_millis() / 1000.0;
    render(deltaTime);

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  glfwSetErrorCallback(NULL);
}

void Application::setup() { glEnable(GL_MULTISAMPLE); }

void Application::clear_screen() {
  glDisable(GL_SCISSOR_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::update_canvas() {};

void Application::render(double deltaTime) {
  update_canvas();
  particle_renderer.shader.activate();
  particle_renderer.shader.set_time(std::chrono::nanoseconds().count() /
                                    1000000000.0f);
  // particle_renderer.shader.set_palette();
  // particle_renderer.shader.set_transform();
  particle_renderer.shader.set_size((settings.particle_size * 1) /
                                    std::min(window_width, window_height));
  particle_renderer.shader.set_detail(3 + settings.particle_size);

  clear_screen();

  particle_renderer.render(window_width, window_height);
}
