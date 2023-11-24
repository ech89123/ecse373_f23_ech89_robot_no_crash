# ecse373_f23_ech89_robot_no_crash  
  
Run these two commands to setup ros:  
`source /opt/ros/noetic/setup.bash`  
`source devel/setup.bash`  
  
The stdr simulator is required to run the project as well as roscpp sensor_msgs geometry_msgs  
To get the stdr simulator: `git clone -b noetic-devel https://github.com/cwru-eecs-275/stdr_simulator.git`    
  
Install dependencies:   
Instal rosdep: `sudo apt install python3-rosdep`    
Initialize rosdep: `sudo rosdep init`    
Update rosdep: `rosdep update`    
Fix permissions of rosdep: `sudo rosdep fix-permissions`    
Install missing dependencies: `rosdep install --from-paths src --ignore-src -r -y`    
  
Make the node runnable: `catkin_make robot_no_crash_node`    
Run the node: `roslaunch robot_no_crash robot_no_crash.launch &` 

Add a Robot by selecting "Create robot" at the top bar of the simulator window  
Also add LIDAR by clicking on the green plus next to the "laser" option  
Then click "Add Robot to Map" and click anywhere on the map to add the robot  
The window already opened will control the robots speed and rotation  
  
To make another controlable robot, run: `rqt`    
Make sure to change the number after robot: `/robot1/cmd_vel` (for a second robot) 
