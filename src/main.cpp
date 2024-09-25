#include "application.hpp"
#include "setting/appSettings.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define SETTINGS_FILE "setting..."

AppSetting setting;

int main() {
  // setting.load_config(SETTINGS_FILE);
  Application app("Particle life", setting);
  app.launch();
  return 0;
}
