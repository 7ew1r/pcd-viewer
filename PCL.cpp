#include "Main.hpp"

extern std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> inputCloud;

void loadPCDFile(std::string filename) {
  pcl::PointCloud<pcl::PointXYZ>::Ptr inputPcd(
      new pcl::PointCloud<pcl::PointXYZ>);
  if (pcl::io::loadPCDFile<pcl::PointXYZ>(filename, *inputPcd) == -1) {
    PCL_ERROR("Couldn't read file \n");
  } else {
    std::cout << "Load PCD File : " << filename << std::endl;
    if (inputCloud.empty() == false) inputCloud.erase(inputCloud.begin());
    inputCloud.push_back(inputPcd);
  }
}

void displayPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud) {
  for (auto point : cloud->points) {
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(point.x, point.y, point.z);
  }
}
