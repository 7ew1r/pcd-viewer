#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

// PCL
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
// #include <pcl/registration/icp.h>
#include <pcl/common/transforms.h>

// Also include GLFW to allow for graphical display
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

// PCL.cpp
void LoadPCDFile(std::string filename);
void DisplayPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud);
void DisplayPointCloud(const pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud,
                       float red, float green, float blue);
void DisplayPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud,
                      float red, float green, float blue,
                      float zoom,
                      float x_offset,
                      float y_offset,
                      float z_offset);

