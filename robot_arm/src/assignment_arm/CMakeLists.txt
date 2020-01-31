cmake_minimum_required(VERSION 2.8.3)
project(assignment_arm)

find_package(catkin REQUIRED COMPONENTS 
 roscpp
   rospy
   std_msgs
   message_generation 
  gazebo_ros 
)

# Depend on system install of Gazebo
find_package(gazebo REQUIRED)

link_directories(${GAZEBO_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS})

 add_message_files(
   FILES
   arm_angle.msg
 )
generate_messages(
   DEPENDENCIES
   std_msgs  # Or other packages containing msgs
 )


catkin_package(
  DEPENDS 
    roscpp 
    message_runtime
    gazebo_ros 
)

add_library(${PROJECT_NAME} src/arm_angle.cpp)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})




## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )


## Generate added messages and services with any dependencies listed here


