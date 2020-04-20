#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

double goal_1[2] = {5.0, 5.0};
double goal_2[2] = {0.0, 0.0};


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

  // Send goal 1
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = goal_1[0];
  goal.target_pose.pose.orientation.w = goal_1[1];

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal 1");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  bool status = ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED;
  
  // Check if the robot reached its goal
  if(status)
    ROS_INFO("Hooray, goal 1 reached");
  else
    ROS_INFO("Booooo, goal 1 was not reached");
  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Simulating object pickup time...\nBut, really we are just waiting for no reason.");
  }
  
  
  // Sending Goal 2
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = goal_2[0];
  goal.target_pose.pose.orientation.w = goal_2[1];

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal 2");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  status = ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED;
  
  // Check if the robot reached its goal
  if(status)
    ROS_INFO("Hooray, goal 2 reached");
  else
    ROS_INFO("Booooo, goal 2 was not reached");
  

  return 0;
}