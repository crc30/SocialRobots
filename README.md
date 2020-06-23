# Installation and documentation Controller Tiago Titanium
Visit
[here](https://github.com/crc30/SocialRobots/blob/master/Report%20SR%20-%20Tiago%20Titanium%20Sign%20-%20Dal%C3%A9%20Castiglione.pdf)
 for a complete report of this project.

## Installation

1. [Download](https://cyberbotics.com/#download) webots
2. [Download](https://github.com/crc30/SocialRobots.git) project from github
3. Open webots
4. Click File > Open Scenario
5. Select file .wbt in /worlds/tiago_world_dale_castiglione.wbt

### How to add a sign


The code divides each part of the body into small arrays of different sizes.
If the values of the movement you would like to perform are not present in the list of arrays in the code, you can add them by creating specific arrays for each part of the body in the following way:

```c
double my_head_torso[3] = {0.00, 0.00, 0.00};

double my_arm[4] = {0.00, 0.00, 0.00, 0.00};

double my_hand[3] = {0.00, 0.00, 0.00};

double my_thumb[5] = {0.00, 0.00, 0.00, 0.00, 0.00};

double my_index[7] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};

double my_middle[7] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};

double my_ring[7] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};

double my_little[7] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};

double my_wheel[2] = {0.00, 0.00};
```

Then you can create the function to perform your sign.
Your custom function will call the main function

```c
static void setTiagoPositionCompos( char *my_names[], int time_step, double interval, double *arm, double *palm, double *thumb, double *index, double *middle, double *ring, double *little );
```

* \*my_names[] contains the names of all the motors present in the robot (no need to modify it, it is already mapped)
* double interval is the value that indicates the time interval that must elapse between the beginning of the gesture and the moment in which the robot must assume that specific position.
* the other variables are arrays of previously declared values.

Suppose you want to create a function that allows the robot to perform the beer sign:

After declaring the arrays, as specified above, you need to create a function as follows:

```c
static void beer(char *names[], int time_step) {
    setTiagoPositionCompos(names, time_step, 0.00, my_arm, my_hand, my_thumb, my_index, my_middle, my_ring, my_little);
    setTiagoPositionCompos(names, time_step, 4.00, my_arm_1, my_hand_1, my_thumb_1, my_index_1, my_middle_1, my_ring_1, my_little_1);
    setTiagoPositionCompos(names, time_step, 2.00, my_arm_2, my_hand_2, my_thumb_2, my_index_2, my_middle_2, my_ring_2, my_little_2);
}
```

As we can see from the code just described, our **beer** function calls the **setTiagoPositionCompos** with the values of the previously declared arrays and a time value (**0.00, 4.00, 2.00**). The time indicator establishes a delay in the execution of the movement towards the indicated gesture from the moment the function is called. The **\*my_names[]** array is the default array for initializing any function that has to do with the robot motors.
To impose a motion on the robot from the position in which it is to the desired one, the function must be set using the arrays **my_arm, my_hand**, etc ..
The integer **int time_step** that we call in each function is initialized in the **main** and returns the value of the basicTimeStep field of the WorldInfo node. The basicTimeStep field defines the duration of the simulation step executed by Webots.

The execution of the functions is managed through keyboard input detection and intercepted through a switch case in the main.

# Documentation

## Function setTiagoPositionCompos

The setTiagoPositionCompos is the main function of our code.
It takes as input the my_names[] array which contains the names of the motors available in the robot, the entire time_step (that returns the value of the basicTimeStep field of the WorldInfo node), the interval which indicates how long the robot must assume that position and the rest of the arrays it takes as input are the values that the robot must assume for each of its motors, the only motors that we do not control, for the simple fact that in our project they are not used, they are the wheels, the head and the engine dedicated to the movement of the bust, for this reason these values are not passed to the function.

## Function main

In the main function are declared the array of available robot motors, a function that takes care of detecting keyboard input and time_step. Then the robot is initialized using the wb_robot_init() function, finally a while cycle is performed, which remains active for the duration of the simulation, in which there is a switch case control that takes care of calling the function relating to the input from the user.

## Function rotate

This function supports the setTiagoPositionCompos and takes care of rotating a certain part of the robot for a certain period of time. These two values are taken as input by the function and this allows their reuse.

## Function rotate_and_move

This function supports the setTiagoPositionCompos and takes care of rotating a part of the robot's body and moving another one simultaneously for a certain period of time and can be integrated into any other function. (Useful in case you need to rotate your wrist while moving your shoulder.)

# Primary Authors
@crc30 \
@fededale95
