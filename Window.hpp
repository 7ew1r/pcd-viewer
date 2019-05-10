#pragma once
#include "Main.hpp"

extern std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> inputCloud;

static double yaw = 0.0, pitch = 0.0, lastX = 0.0, lastY = 0.0;
static int ml = 0;

class Window {
 private:
  GLFWwindow *const window;

 public:
  Window(int width = 1280, int height = 960, const char *title = "main")
      : window(glfwCreateWindow(width, height, title, NULL, NULL)) {
    if (window == NULL) {
      std::cerr << "Can't create GLFW window." << std::endl;
      exit(1);
    }
    // set current window to control taget
    glfwMakeContextCurrent(window);

    // wait for vertical sync
    glfwSwapInterval(1);

    // window resize
    glfwSetWindowSizeCallback(window, resize);
    resize(window, width, height);
  }

  virtual ~Window() { glfwDestroyWindow(window); }

  void windowSetting(std::string setting) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)640 / 480, 0.01f, 20.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, 0, 0, 0, 1, 0, -1, 0);
    glTranslatef(0, 0, +0.5f);
    glRotated(pitch, 1, 0, 0);
    glRotated(yaw, 0, 1, 0);
    glTranslatef(0, 0, -0.5f);

    // We will render our depth data as a set of points in 3D space
    glPointSize(2);
    glEnable(GL_DEPTH_TEST);
  }

  static void on_mouse_button(GLFWwindow *win, int button, int action,
                              int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) ml = action == GLFW_PRESS;
  }
  static double clamp(double val, double lo, double hi) {
    return val < lo ? lo : val > hi ? hi : val;
  }
  static void on_cursor_pos(GLFWwindow *win, double x, double y) {
    if (ml)

    {
      yaw = clamp(yaw - (x - lastX), -120, 120);
      pitch = clamp(pitch + (y - lastY), -80, 80);
    }
    lastX = x;
    lastY = y;
  }

  void makeContextCurrent() { glfwMakeContextCurrent(window); }

  int shouldClose() const {
    return glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE);
  }

  // Process when D & D a file into window
  static void drop_callback(GLFWwindow *window, int count, const char **paths) {
    std::cout << paths[0] << std::endl;
    std::string path = std::string(paths[0]);
    loadPCDFile(path);
  }

  void swapBuffers() {
    // swap color buffer
    glfwSwapBuffers(window);

    glfwPollEvents();

    glfwSetDropCallback(window, drop_callback);
    glfwSetCursorPosCallback(window, on_cursor_pos);
    glfwSetMouseButtonCallback(window, on_mouse_button);
  }

  static void resize(GLFWwindow *const window, int width, int height) {
    // set the entire window as a viewport
    glViewport(0, 0, width, height);
  }
};
