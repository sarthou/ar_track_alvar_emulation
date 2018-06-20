#include "visualization_msgs/Marker.h"

#include <ros/ros.h>
#include <ros/package.h>
#include <vector>
#include <string>

struct ar_marker
{
  float pose_x;
  float pose_y;
  float pose_z;

  float or_x;
  float or_y;
  float or_z;
  float or_w;
  std::string ns;
};

int main(int argc, char**argv)
{
  ros::init(argc, argv, "ar_track_alvar_emulator");
	ros::NodeHandle n;

  ros::Publisher pub;
  pub = n.advertise <visualization_msgs::Marker> ("ar_visualization_marker", 0);


  std::string path = ros::package::getPath("ar_track_alvar_emulation");
  path += "/file/tmp.txt";

   FILE * pFile;
   pFile = fopen (path.c_str(),"r");
   rewind (pFile);

   ar_marker tmp;
   char ns[100];
   while(fscanf (pFile, "%s [%f %f %f] [%f %f %f %f]\n",
                ns,
                &tmp.pose_x,
                &tmp.pose_y,
                &tmp.pose_z,
                &tmp.or_x,
                &tmp.or_y,
                &tmp.or_z,
                &tmp.or_w
              ) != EOF)
  {
    tmp.ns = std::string(ns);

    visualization_msgs::Marker marker;
    marker.pose.position.x = tmp.pose_x;
    marker.pose.position.y = tmp.pose_y;
    marker.pose.position.z = tmp.pose_z;

    marker.pose.orientation.x = tmp.or_x;
    marker.pose.orientation.y = tmp.or_y;
    marker.pose.orientation.z = tmp.or_z;
    marker.pose.orientation.w = tmp.or_w;

    marker.ns = tmp.ns;
    pub.publish(marker);
  }
   fclose (pFile);

  return 0;
}
