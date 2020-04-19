#!/bin/sh

# Change to our simple demo map
# export TURTLEBOT_GAZEBO_WORLD_FILE=/home/workspace/RoboND_Project5/catkin_ws/src/world/basic.world

# Launch world
xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" & 

sleep 5

# Launch AMCL
xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch" & 

sleep 5

# Launch rviz
xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" 