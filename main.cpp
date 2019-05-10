#include "main.hpp"
#include "Window.hpp"

std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> inputCloud;

int main() {
  // Initialize GLFW
  if (glfwInit() == GL_FALSE) {
    std::cerr << "Can't initialize GLFW" << std::endl;
    return -1;
  }

  atexit(glfwTerminate);

  Window win(640, 480, "MainWindow");

  while (win.shouldClose() == GL_FALSE) {
    win.makeContextCurrent();
    win.windowSetting("main");

    glBegin(GL_POINTS);

    for (auto cloud : inputCloud) {
      displayPointCloud(cloud);
    }

    glEnd();

    win.swapBuffers();
  }
  return 0;
}
