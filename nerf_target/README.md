<img src="http://www.modrobotics.com/wp-content/uploads/2016/05/mr_logo.png"  alt="Modular Robotics" width="100"/>

#Nerf Target
This is a little robot with a moving target. Once the target has been knocked down
lights and sounds will be emitted to celebrate shortly before the target is
automatically reset.

TODO: Show gif of the robot in action

##How to build this robot:
The absolute minimum: You need a couple Drive Cubelets for moving the target, a
Distance Cubelet for detecting when the target has been knocked down and a Rotate
Cubelet for resetting the target. You can add Speaker and Flashlight Cubelets for flare.
We also made use of Brick Adaptors and some Legos we had laying around to support the target
and provide and 'arm' to the Rotate Cubelet for resetting the target.

[Virtual Front View](img/front_view-virtual.PNG)

[Virtual Bottom View](img/bottom_view-virtual.PNG)



##What needs to be reprogrammed:
* All of the drive blocks in the construction with [drives.c](drives.c)
* The rotate block used to reset the target with [rotate.c](rotate.c)
* A 'brain' block in the construction used to control the state of the robot with brain.c
  * This should be a block that doesn't need to exhibit any other behavior such as a Battery Cubelet.
