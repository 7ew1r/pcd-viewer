#pragma once
#include "main.hpp"

extern std::vector< pcl::PointCloud< pcl::PointXYZ>::Ptr > input_cloud;
extern pcl::PointCloud< pcl::PointXYZ>::Ptr saved_cloud;

static double yaw = 0.0, pitch = 0.0, lastX = 0.0, lastY = 0.0; static int ml = 0;

extern int isFPS;

class Window
{
private:
    GLFWwindow *const window;
    
public:
    // コンストラクタ
    Window(int width = 1280, int height = 960, const char *title = "main")
        : window(glfwCreateWindow(width, height, title, NULL, NULL))
    {
        if (window == NULL)
        {
            std::cerr << "Can't create GLFW window." << std::endl;
            exit(1);
        }
        // 現在のウィンドウを処理対象にする
        glfwMakeContextCurrent(window);

        // 垂直同期のタイミングを待つ
        glfwSwapInterval(1);

         // ウィンドウのサイズ変更時に呼び出す処理の登録
        glfwSetWindowSizeCallback(window, resize);
        // 開いたウィンドウの初期設定
        resize(window, width, height);
    }

    // デストラクタ
    virtual ~Window()
    {
        glfwDestroyWindow(window);
    }

    void windowSetting(std::string setting)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, (float)640/480, 0.01f, 20.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        if(setting == "main"){
            gluLookAt(0,0,0, 0,0,1, 0,-1,0);
        } else {
            gluLookAt(0.5, -0.5, -0.5,
                      0, 0, 1,
                      0, -1, 0);
        }
        glTranslatef(0,0,+0.5f);
        // if(setting == "main") glRotated(0, 1, 0, 0);
        // else 
        glRotated(pitch, 1, 0, 0);
        // if(setting == "main") glRotated(0, 0, 1, 0);
        // else 
        glRotated(yaw, 0, 1, 0);
        glTranslatef(0,0,-0.5f);

        // We will render our depth data as a set of points in 3D space
        glPointSize(2);
        glEnable(GL_DEPTH_TEST);
    }

    static void on_mouse_button(GLFWwindow * win, int button, int action, int mods)
    {
        if(button == GLFW_MOUSE_BUTTON_LEFT) ml = action == GLFW_PRESS;
    }
    static double clamp(double val, double lo, double hi) { return val < lo ? lo : val > hi ? hi : val; }
    static void on_cursor_pos(GLFWwindow * win, double x, double y)
    {
        if(ml)

        {
            yaw = clamp(yaw - (x - lastX), -120, 120);
            pitch = clamp(pitch + (y - lastY), -80, 80);
        }
        lastX = x;
        lastY = y;
    }

    void makeContextCurrent(){
        glfwMakeContextCurrent(window);
    }

    // ウィンドウを閉じるべきかを判定する
    int shouldClose() const
    {
        return glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE);
    }


    static void drop_callback(GLFWwindow* window, int count, const char** paths)
    {
        std::cout << paths[0] << std::endl;
        std::string path = std::string(paths[0]);
        LoadPCDFile( path );
    }

    // カラーバッファを入れ替えてイベントを取り出す
    void swapBuffers()
    {
        // カラーバッファを入れ替える
        glfwSwapBuffers(window);

        // イベントを取り出す
        glfwPollEvents();

        glfwSetDropCallback(window, drop_callback);
        //glfwSetKeyCallback(window, key_callback);
        glfwSetCursorPosCallback(window, on_cursor_pos);
        glfwSetMouseButtonCallback(window, on_mouse_button);
        //glfwSetScrollCallback(window, wheel_callback);
    }
    // ウィンドウのサイズ変更時の処理
    static void resize(GLFWwindow *const window, int width, int height)
    {
        // ウィンドウ全体をビューポートに設定する
        glViewport(0, 0, width, height);
    }
};
