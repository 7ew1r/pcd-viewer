#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

// PCL
#include <pcl/common/transforms.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

// Also include GLFW to allow for graphical display
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

void loadPCDFile(std::string filename);
void displayPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud);
