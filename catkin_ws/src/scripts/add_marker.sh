#!/bin/sh

# Change to our simple demo map
export TURTLEBOT_GAZEBO_WORLD_FILE=/home/workspace/RoboND_Project5/catkin_ws/src/world/basic.world
export TURTLEBOT_GAZEBO_MAP_FILE=/home/workspace/RoboND_Project5/catkin_ws/src/map/basic.yaml

# Launch world
xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" & 
sleep 5

# Launch AMCL
xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch" & 
sleep 5

# Launch rviz
# xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; rosrun rviz rviz -d /home/workspace/RoboND_Project5/catkin_ws/src/rvizConfig/full.rviz" &
sleep 5

# Launch virtual object
xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; rosrun add_markers add_markers" & 
# sleep 5

# Launch pick
# xterm -e " source /home/workspace/RoboND_Project5/catkin_ws/devel/setup.bash; rosrun pick_objects pick_objects"