<img src="http://www.modrobotics.com/wp-content/uploads/2016/05/mr_logo.png"  alt="Modular Robotics" width="100"/>

#Simple Line Follower
A simple line following robot. The robot relies on a reflective surface with a dull line drawn on it. ie: white table (or paper) with a dark line.

![Front View](/img/front_view-virtual.PNG)

![Bottom View](/img/bottom_view-virtual.PNG)

##How to build this robot
Take two Drive Cubelets, attach a Distance Cubelet to each, separate with a Blocker Cubelet and attach a battery.

##Which blocks need Reprogrammed
Flash [line_detect.c](line_detect.c) to both Distance Sensors. Test the robot and modify the `DEFAULT_THRESHOLD` as needed.
