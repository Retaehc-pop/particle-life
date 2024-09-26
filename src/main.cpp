#include "application.hpp"
#include "setting/appSettings.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#define SETTINGS_FILE "setting..."
const std::string window_name = "Particle Life";
AppSetting setting;

int main() {
  // setting.load_config(SETTINGS_FILE);
  Application app("Particle Life", setting.fullscreen);
  app.launch();
  return 0;
}
