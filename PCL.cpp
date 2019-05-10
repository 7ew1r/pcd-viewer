#include "main.hpp"

extern std::vector< pcl::PointCloud< pcl::PointXYZ>::Ptr > input_cloud;

void LoadPCDFile(std::string filename){
    pcl::PointCloud<pcl::PointXYZ>::Ptr input_pcd (new pcl::PointCloud<pcl::PointXYZ>);
    if (pcl::io::loadPCDFile<pcl::PointXYZ> (filename, *input_pcd) == -1)
    {
        PCL_ERROR ("Couldn't read file \n");
    } else {
        std::cout << "Load PCD File : " << filename << std::endl;
        if (input_cloud.empty() == false) input_cloud.erase(input_cloud.begin());
        input_cloud.push_back(input_pcd);
    }
}

void DisplayPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud)
{
    for (auto point : cloud->points){
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(point.x, point.y, point.z);
    }
}
