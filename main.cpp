#include "main.hpp"
#include "Window.hpp"

int isFPS = 1;

bool saved_cloud_is_empty = true;

std::vector< pcl::PointCloud< pcl::PointXYZ>::Ptr > input_cloud;
pcl::PointCloud< pcl::PointXYZ>::Ptr saved_cloud;

int main()
{
    // Initialize GLFW
    if (glfwInit() == GL_FALSE)
    {
        std::cerr << "Can't initialize GLFW" << std::endl;
        return -1;
    }

    // プログラム終了時の処理を登録する
    atexit(glfwTerminate);

    Window win(640, 480, "MainWindow");
    // Window win2(640, 480, "SecondWindow");

    while (win.shouldClose() == GL_FALSE )
    {
        win.makeContextCurrent();
        win.windowSetting("main");
        
        glBegin(GL_POINTS);

        for(auto cloud: input_cloud){
            DisplayPointCloud(cloud);
        }

        glEnd();

        win.swapBuffers();

        // win2.makeContextCurrent();
        // win2.windowSetting("second");
        // glBegin(GL_POINTS);

        // for(auto cloud: input_cloud){
        //     DisplayPointCloud(cloud);
        // }

        // glEnd();

        // win2.swapBuffers();

    }
    return 0;
}
