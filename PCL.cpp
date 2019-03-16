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

void PassThroughFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, std::string fieldName, float limitsMin, float limitsMax){
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud (cloud);
    pass.setFilterFieldName (fieldName);
    pass.setFilterLimits (limitsMin, limitsMax);
    pass.filter (*cloud);
}

void VoxelGridFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud){
    pcl::ApproximateVoxelGrid<pcl::PointXYZ> approximate_voxel_filter;
    approximate_voxel_filter.setLeafSize(0.01f, 0.01f, 0.01f);
    approximate_voxel_filter.setInputCloud(cloud);
    approximate_voxel_filter.filter(*cloud);
}

void IterativeClosestPoint(pcl::PointCloud<pcl::PointXYZ>::Ptr &source, pcl::PointCloud<pcl::PointXYZ>::Ptr &target ){
    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
    icp.setInputSource(source);
    icp.setInputTarget(target);
    icp.align(*source);
    std::cout << "has converged:" << icp.hasConverged() << " score: " <<
        icp.getFitnessScore() << "\n";
    std::cout << icp.getFinalTransformation() << "\n";
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

pcl::PointCloud<pcl::PointXYZ>::Ptr merge_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud1, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud2)
{
    pcl::PointCloud<pcl::PointXYZ> cloud_merged;
    cloud_merged = *cloud1;
    cloud_merged += *cloud2;

    return cloud_merged.makeShared();
}

