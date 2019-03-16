#include "main.hpp"
#include "Window.hpp"

//#include "Realsense.hpp"


int isFPS = 1;

bool saved_cloud_is_empty = true;

std::vector< pcl::PointCloud< pcl::PointXYZ>::Ptr > input_cloud;
pcl::PointCloud< pcl::PointXYZ>::Ptr saved_cloud;

int main()
{
    // GLFW を初期化する
    if (glfwInit() == GL_FALSE)
    {
        // 初期化に失敗した
        std::cerr << "Can't initialize GLFW" << std::endl;
        return -1;
    }

    // プログラム終了時の処理を登録する
    atexit(glfwTerminate);

    //  RealSense realsense;
    Window win(640, 480, "MainWindow");
    Window win2(640, 480, "SecondWindow");
    //Window win2;

    // ウィンドウが開いている間繰り返す
    while (win.shouldClose() == GL_FALSE )
    {
        win.makeContextCurrent();
        win.windowSetting("main");
        
        glBegin(GL_POINTS);

//        if(!saved_cloud_is_empty) DisplayPointCloud(saved_cloud);
        for(auto cloud: input_cloud){
            DisplayPointCloud(cloud);
        }

        glEnd();
        // カラーバッファを入れ替える
        win.swapBuffers();

        win2.makeContextCurrent();
        win2.windowSetting("second");
        glBegin(GL_POINTS);

        for(auto cloud: input_cloud){
            DisplayPointCloud(cloud);
        }

        glEnd();

        win2.swapBuffers();


        /*
        win2.makeContextCurrent();
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, (float)1280/960, 0.01f, 20.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(c_eyeX, c_eyeY, c_eyeZ, c_centerX, centerY, c_centerZ, c_pX, c_upY, c_upX);
        glTranslatef(0,0,+0.5f);
        glRotated(pitch, 1, 0, 0);
        glRotated(yaw, 0, 1, 0);
        glTranslatef(0,0,-0.5f);

        glPointSize(2);
        glEnable(GL_DEPTH_TEST);
        glBegin(GL_POINTS);

        glEnd();
        win2.swapBuffers();
        */

    }
    return 0;
}
