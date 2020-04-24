#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


double x[2] = {-2.9, 1.5};
double y[2] = {0.25, 1.7};
double w[2] = {0.0, 1.0};


void simulatePickup(){
  // Wait 5 sec to simulate object pickup
  ROS_INFO("Simulating object pickup");
  ROS_INFO("Picking up object... ");
  ros::Duration(5.0).sleep();
  ROS_INFO("Pickup complete");
}


int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = x[0];
  goal.target_pose.pose.position.y = y[0];
  goal.target_pose.pose.orientation.w = w[0];

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup location");
  ac.sendGoal(goal);
  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Pickup location reached");
    
    simulatePickup();
  
    // Define a position and orientation for the robot to reach
    goal.target_pose.pose.position.x = x[1];
    goal.target_pose.pose.position.y = y[1];
    goal.target_pose.pose.orientation.w = w[1];

    // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending dropoff location");
    ac.sendGoal(goal);
    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Drop-off location reached");
    else
      ROS_INFO("Failed to reach Drop-off location");
  }
  else{
    ROS_INFO("Failed to reach pickup location");
  }
  

  
  ros::spin();
  return 0;
}