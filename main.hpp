
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

// PCL
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/approximate_voxel_grid.h>

// Librealsense
//#include <librealsense/rs.hpp>

// Also include GLFW to allow for graphical display
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

// PCL.cpp
void LoadPCDFile(std::string filename);

void PassThroughFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, std::string fieldName, float limitsMin, float limitsMax);

void VoxelGridFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud);

void IterativeClosestPoint(pcl::PointCloud<pcl::PointXYZ>::Ptr &source, pcl::PointCloud<pcl::PointXYZ>::Ptr &target );

void DisplayPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud);

void DisplayPointCloud(const pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud,
                       float red, float green, float blue);

void DisplayPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud,
                      float red, float green, float blue,
                      float zoom,
                      float x_offset,
                      float y_offset,
                      float z_offset);

pcl::PointCloud<pcl::PointXYZ>::Ptr merge_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud1, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud2);
