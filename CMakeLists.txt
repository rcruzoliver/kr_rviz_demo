cmake_minimum_required(VERSION 3.8)
project(kr_rviz_demo)


# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-std=c++2a -O3 -Wfatal-errors -pedantic -Wall -Wextra)
endif()

# uncomment the following section in order to fill in
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(Threads REQUIRED)
find_package(tf2_ros REQUIRED)
include_directories(include)
add_definitions(-DCONFIG_DEFAULT_LOGLEVEL=1)

add_executable(state_publisher src/state_publisher.cpp)


ament_target_dependencies(state_publisher rclcpp geometry_msgs std_msgs tf2_ros)
target_link_libraries(state_publisher)


# Install targets
install(TARGETS
  state_publisher
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch/
    DESTINATION share/${PROJECT_NAME}/launch
)

install(
    DIRECTORY urdf
    DESTINATION share/${PROJECT_NAME}
)

install(
    DIRECTORY meshes 
    DESTINATION share/${PROJECT_NAME})

install(
    DIRECTORY rviz 
    DESTINATION share/${PROJECT_NAME})


ament_package()

