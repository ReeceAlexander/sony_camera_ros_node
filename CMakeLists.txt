# cmake_minimum_required(VERSION 3.0.2)

# project(sony_camera_ros_node)

# ## Find required packages
# find_package(catkin REQUIRED COMPONENTS
#   roscpp
#   std_msgs
# )

# ## Include paths
# set(CrSDK_INCLUDE_DIR "/home/reece/Downloads/CrSDK_v1.13.00_20241016a_Linux64PC/app/CRSDK")
# set(CrSDK_LIBRARY_DIR "/home/reece/Downloads/CrSDK_v1.13.00_20241016a_Linux64PC/external/crsdk")

# include_directories(
#   include
#   ${catkin_INCLUDE_DIRS}
#   ${CrSDK_INCLUDE_DIR}
# )

# ## Link directories
# link_directories(
#   ${CrSDK_LIBRARY_DIR}
# )

# ## Add executable
# add_executable(sony_camera_node src/sony_camera_node.cpp)

# ## Link libraries
# target_link_libraries(sony_camera_node
#   ${catkin_LIBRARIES}
#   Cr_Core  # Link by library name, not full path
# )

# ## Declare a catkin package
# catkin_package()

cmake_minimum_required(VERSION 3.0.2)

project(sony_camera_ros_node)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

# Add paths for CrSDK
set(CrSDK_INCLUDE_DIR "/home/reece/Downloads/CrSDK_v1.13.00_20241016a_Linux64PC/app/CRSDK")

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${CrSDK_INCLUDE_DIR}  # Include the path to Camera SDK headers
)

# Link directories for CrSDK
set(CrSDK_LIBRARY_DIR "/home/reece/Downloads/CrSDK_v1.13.00_20241016a_Linux64PC/external")
link_directories(${CrSDK_LIBRARY_DIR})

add_executable(sony_camera_node src/sony_camera_node.cpp)

set_target_properties(sony_camera_node PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CATKIN_DEVEL_PREFIX}/lib/${PROJECT_NAME}
)

# Link the necessary SDK libraries
target_link_libraries(sony_camera_node
  ${catkin_LIBRARIES}
  ${CrSDK_LIBRARY_DIR}/crsdk/libCr_Core.so  # Link the Camera SDK libraries
)

catkin_package()
