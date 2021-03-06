#!/bin/sh

export TURTLEBOT_GAZEBO_WORLD_FILE=/home/workspace/RoboND_Project5/catkin_ws/src/world/basic.world

xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" & 

sleep 5

# xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; rosrun gmapping slam_gmapping" & 
xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; roslaunch gmapping slam_gmapping.launch" & 


sleep 5

xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" & 

sleep 5

xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch"