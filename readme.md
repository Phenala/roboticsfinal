# Robotics Lab Project

Group Members|ID
-------------|--------------
**Milky Bekele**|ATR/9584/08
**Nathnael Dejene**|ATR/0112/08
**Same Michael**|ATR/2759/08
**Samuel Sisay**|ATR/0607/08


## Robot Arm




## Wheeled Robots

### 1. Creating The Robots

The two wheeled robot along with the additional quadruped and six-wheeled robot are in the 
*robots.world* file in the roboticsfinal/robot directory.

![Image of Robots](https://i.imgur.com/zicJnJw.jpg)

Models: 
	**My_Robot** - Two Wheeled Robot, **My_Robot_Four** - Quadruped Robot, **My_Robot_Six** - Six Wheeled Robot with scooper

To preview the world:

- Copy models in roboticsfinal/robot/models to .gazebo/models
- Open terminal in roboticsfinal/robot directory and run `gazebo robots.world`
 *Warning: World will fail to open if models are not copied.*


### 2. Adding The Sensors

The Two wheeled robot (My Robot) has:

- Laser scan sensor
- Camera sensor
- Contact sensors on both wheels and body

The sensor data is available on the following topics:

	/gazebo/default/my_robot/camera/link/camera/image
	/gazebo/default/my_robot/hokuyo/link/laser/scan
	/gazebo/default/my_robot/left_wheel/left_wheel_contact
	/gazebo/default/my_robot/left_wheel/left_wheel_contact/contacts
	/gazebo/default/my_robot/right_wheel/right_wheel_contact
	/gazebo/default/my_robot/right_wheel/right_wheel_contact/contacts
	/gazebo/default/my_robot_four/chassis/body_contact
	/gazebo/default/my_robot_four/chassis/body_contact/contacts


### 3. Wheel Rotate Plugin

All the robots have plugins attached that allows locomotion within the world.
To run the plugin:

- Go to the roboticsfinal/robot folder on terminal.
- Run `export GAZEBO_PLUGIN_PATH=$HOME/lab/project/robot/twowheel/build:$GAZEBO_PLUGIN_PATH` *Replace ($HOME/lab) with the absolute path of the directory.*
- `gzserver -u robots.world`
- Open new terminal, run `gzclient`
- Press play on the Gazebo interface.
- Watch them go!


### 4. ROSLaunch World

To start the world with roslaunch, go to the roboticsfinal/robot/robotros directory and run:
- `source devel/setup.bash`
- `roslaunch robot_gazebo robots.launch`
