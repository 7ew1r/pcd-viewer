#include "main.hpp"

extern std::vector< pcl::PointCloud< pcl::PointXYZ>::Ptr > input_cloud;
extern pcl::PointCloud< pcl::PointXYZ>::Ptr saved_cloud;

extern bool saved_cloud_is_empty;

void LoadPCDFile(std::string filename){
    pcl::PointCloud<pcl::PointXYZ>::Ptr input_pcd (new pcl::PointCloud<pcl::PointXYZ>);
    if (pcl::io::loadPCDFile<pcl::PointXYZ> (filename, *input_pcd) == -1)
    {
        PCL_ERROR ("Couldn't read file \n");
    } else {
        std::cout << "Load PCD File : " << filename << std::endl;
        input_cloud.push_back(input_pcd);
    }
}

void DisplayPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud)
{
    for (size_t i = 0; i < cloud->points.size (); ++i){
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(cloud->points[i].x, cloud->points[i].y, cloud->points[i].z);
    }
}

void DisplayPointCloud(const pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud,
                       float red, float green, float blue)
{
    for (size_t i = 0; i < cloud->points.size (); ++i){
        glColor3f(red, green, blue);
        glVertex3f(cloud->points[i].x, cloud->points[i].y,cloud->points[i].z);
    }
}

void DisplayPointCloud(const pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud,
                      float red, float green, float blue,
                      float zoom,
                      float x_offset,
                      float y_offset,
                      float z_offset)
{
    for (size_t i = 0; i < cloud->points.size (); ++i){
        glColor3f(red, green, blue);
        glVertex3f(cloud->points[i].x/zoom+x_offset, cloud->points[i].y/zoom+y_offset,cloud->points[i].z/zoom+z_offset);
    }
}


