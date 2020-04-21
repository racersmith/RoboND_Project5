#!/bin/sh

apt-get update && apt-get upgrade -y
git config --global user.name "Josh Smith"
git config --global user.email "racersmith@gmail.com"
git config --global credential.helper 'cache --timeout=9999'
pip install rospkg
cd catkin_ws
catkin_make