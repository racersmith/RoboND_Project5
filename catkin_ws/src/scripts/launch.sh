#!/bin/sh

# Change to our simple demo map
export TURTLEBOT_GAZEBO_WORLD_FILE=/home/workspace/RoboND_Project5/catkin_ws/src/world/basic.world

# Launch Gazebo Simulation
xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" & 
sleep 5

# Launch roscore
xterm -e " source /opt/ros/kinetic/setup.bash; roscore" &
sleep 5

# Launch rviz
xterm -e " rosrun rviz rviz"
