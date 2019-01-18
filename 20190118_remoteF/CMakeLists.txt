cmake_minimum_required(VERSION 2.8.3)
project(remoteF)


add_compile_options(-std=c++11)
find_package(catkin REQUIRED COMPONENTS
  nav_msgs
  roscpp
  rospy
  sensor_msgs
  std_msgs
  tf
  image_transport
  OpenCV
  message_generation
)

add_message_files(
   FILES
  control.msg
 )
generate_messages(
	DEPENDENCIES
)

catkin_package(CATKIN_DEPENDS
 message_runtime)
include_directories(
"/usr/include/eigen3")




include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)



add_executable(testGui src/main.cpp)
add_library(remoteUI src/remote.cpp)
target_link_libraries(testGui ${catkin_LIBRARIES} remoteUI)
