#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

double goal_1[3] = {-5.0, -1.5, -1.0};
double goal_2[3] = {0.0, 0.0, 0.0};


bool moveTo(double x, double y, double w){
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
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.w = w;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal pose");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  bool status = ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED;
  
  // Check if the robot reached its goal
  if(status)
    ROS_INFO("Hooray, goal reached");
  else
    ROS_INFO("Booooo, goal was not reached");
  
  return status;
  }


int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  bool status;
  status = moveTo(goal_1[0], goal_1[0], goal_1[0]);
    
  if (status){
    // Wait 5 sec for move_base action server to come up
    ROS_INFO("Simulating object pickup time...\nBut, really we are just waiting for no reason.");
    ros::Duration(5.0).sleep();
	status = moveTo(goal_2[0], goal_2[0], goal_2[0]);
  }
  

  return 0;
}