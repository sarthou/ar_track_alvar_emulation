#include "visualization_msgs/Marker.h"

#include <ros/ros.h>
#include <ros/package.h>
#include <vector>
#include <string>

struct ar_marker
{
  double pose_x;
  double pose_y;
  double pose_z;

  double or_x;
  double or_y;
  double or_z;
  double or_w;
  std::string ns;
};

std::vector<ar_marker> ar_markers;

void CallbackObj(const visualization_msgs::Marker::ConstPtr& msg)
{
  int index = -1;
  for(size_t i = 0; i < ar_markers.size(); i++)
    if(ar_markers[i].ns == msg->ns)
    {
      index = i;
      break;
    }

  if(index == -1)
  {
    index = ar_markers.size();
    ar_marker tmp;
    tmp.ns = msg->ns;
    ar_markers.push_back(tmp);
  }

  ar_markers[index].pose_x = msg->pose.position.x;
  ar_markers[index].pose_y = msg->pose.position.y;
  ar_markers[index].pose_z = msg->pose.position.z;

  ar_markers[index].or_x = msg->pose.orientation.x;
  ar_markers[index].or_y = msg->pose.orientation.y;
  ar_markers[index].or_z = msg->pose.orientation.z;
  ar_markers[index].or_w = msg->pose.orientation.w;
}

int main(int argc, char**argv)
{
  ros::init(argc, argv, "ar_track_alvar_listener");
	ros::NodeHandle n;

  ros::Subscriber sub;
  sub = n.subscribe("ar_visualization_marker", 1, CallbackObj);

  ros::spin();

  std::string path = ros::package::getPath("ar_track_alvar_emulation");
  path += "/file/tmp.txt";

   FILE * pFile;
   pFile = fopen (path.c_str(),"w");
   for(size_t i = 0; i < ar_markers.size(); i++)
   {
     fprintf (pFile, "%s [%f %f %f] [%f %f %f %f]\n",
              ar_markers[i].ns.c_str(),
              ar_markers[i].pose_x,
              ar_markers[i].pose_y,
              ar_markers[i].pose_z,
              ar_markers[i].or_x,
              ar_markers[i].or_y,
              ar_markers[i].or_z,
              ar_markers[i].or_w
            );
   }
   fclose (pFile);

  return 0;
}
