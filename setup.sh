#!/bin/sh

# Update workspace
apt-get update && apt-get upgrade -y

# Install missing package
pip install rospkg

# Configure git
git config --global user.name "Josh Smith"
git config --global user.email "racersmith@gmail.com"
git config --global credential.helper 'cache --timeout=9999'

# Grab latest
git pull origin master

# Make the package
cd catkin_ws
catkin_make