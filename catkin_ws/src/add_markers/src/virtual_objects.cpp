// subscribe to move_base/status
// status_list.status
// 1 == goal accepted, trying to reach goal
// 3 == goal reached
// This will tell us if we should pick up or put down the object

// subscribe to move_base/current_goal
// gemoetry_msgs/PoseStamped

// #include <move_base_msgs/MoveBaseAction.h>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>


double goal_1[4] = {-3.00, 0.116, -0.75, 0.65};
double goal_2[4] = {1.49, 1.43, -0.03, 0.99};

int step = 0;

float box_size=0.25;
float color[3] = {1.0, 0.0, 0.69};


void goalPositionCb(const 


int main( int argc, char** argv ) {
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "pick_object";
  marker.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = visualization_msgs::Marker::CUBE;

  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  marker.action = visualization_msgs::Marker::ADD;
  
  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = box_size;
  marker.scale.y = box_size;
  marker.scale.z = box_size;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = color[0];
  marker.color.g = color[1];
  marker.color.b = color[2];
  marker.color.a = 1.0;
  
  marker.lifetime = ros::Duration();
  
  // Wait for our viz subscriber
  while(marker_pub.getNumSubscribers() < 1){
    ROS_WARN_ONCE("Please create a subscriber to the marker");
    sleep(1);
  }
  
  ROS_INFO("Subscriber found");
  
  while (ros::ok() && step < 10) {
    switch(step) {
      case 0: // Pickup
        ROS_INFO("Object placed at pickup location");
        marker.pose.position.x = goal_1[0];
        marker.pose.position.y = goal_1[1];
        marker.color.a = 1.0;
        step=1;
        break;
        
      case 1: // Transit
        ROS_INFO("Object in transit to drop-off location");
        marker.pose.position.x = goal_1[0];
        marker.pose.position.y = goal_1[1];
        marker.color.a = 0.0;
        step=2;
        break;

      case 2: // Goal
        ROS_INFO("Object placed at drop-off location");
        marker.pose.position.x = goal_2[0];
        marker.pose.position.y = goal_2[1];
        marker.color.a = 1.0;
        step=100;
        break;
    }
    marker_pub.publish(marker);
    ros::Duration(5.0).sleep();
  }
  ros::spin();
}