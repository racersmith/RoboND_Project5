// subscribe to move_base/result
// move_base_msgs/MoveBaseActionResult
// status.status
// 1 == goal accepted, trying to reach goal
// 3 == goal reached
// This will tell us if we should pick up or put down the object

// subscribe to move_base/current_goal
// geometry_msgs/PoseStamped

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <geometry_msgs/PoseStamped.h>


int step = 0;

float box_size=0.25;
float color[3] = {1.0, 0.0, 0.69};

double box_pose[2];
bool ready = false;

void goal_cb(const geometry_msgs::PoseStamped& goal){
  ROS_INFO("Recieved Goal in virtual objects");
  box_pose[0] = goal.pose.position.x;
  box_pose[1] = goal.pose.position.y;
  ready = true;
}

void result_cb(const move_base_msgs::MoveBaseActionResult& result){
  ROS_INFO("Status recieved in virtual objects"); 
  if (result.status.status == 3){
    step++;
  }
}


int main( int argc, char** argv ) {
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber goal_pose_sub = n.subscribe("/move_base/current_goal", 1, goal_cb);
  ros::Subscriber result_sub = n.subscribe("/move_base/result", 1, result_cb);
  ros::Rate loop_rate(10);
  
  
  // Marker setup
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
  marker.color.a = 0.0;
  
  marker.lifetime = ros::Duration();
  
  // Wait for our viz subscriber
  while(marker_pub.getNumSubscribers() < 1){
    ROS_WARN_ONCE("Please create a subscriber to the marker");
    ros::spinOnce();
    loop_rate.sleep();
  }
  
  
  // Wait for first goal pose
  while(!ready){
    ROS_INFO_ONCE("Waiting for pickup location");
    ros::spinOnce();
    loop_rate.sleep();
  }
  
  
  
  while (ros::ok() && step < 10) {
    switch(step) {
      case 0: // Pickup
        ROS_INFO("Object placed at pickup location");
        marker.pose.position.x = box_pose[0];
        marker.pose.position.y = box_pose[1];
        marker.color.a = 1.0;
        step=1;
        marker_pub.publish(marker);
        break;
        
      case 1: // Transit
        ROS_INFO("Object in transit to drop-off location");
        marker.color.a = 0.0;
        step=2;
        marker_pub.publish(marker);
        break;

      case 2: // Goal
        ROS_INFO("Object placed at drop-off location");
        marker.pose.position.x = box_pose[0];
        marker.pose.position.y = box_pose[1];
        marker.color.a = 1.0;
        step=100;
        marker_pub.publish(marker);
        break;
    }
    ros::spinOnce();
    loop_rate.sleep();
  }
  ros::spin();
}