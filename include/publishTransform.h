// Author: Raul Cruz-Oliver
// Date, place: November 2023, Butikkon, CH

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/msg/transform_stamped.hpp>
// #include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/point.hpp>

#include <chrono>
#include <cmath>

inline void publishTransform(const std::string &frame_id, const std::string &child_frame_id,
	                      double x, double y, double z,
	                      tf2_ros::TransformBroadcaster &tf_broadcaster,
						  const rclcpp::Node &node)
	{
	    const double mm_to_m = 0.001;
	    geometry_msgs::msg::TransformStamped transform;
	    transform.header.stamp = node.now();
	    transform.header.frame_id = frame_id;
	    transform.child_frame_id = child_frame_id;
	    transform.transform.translation.x = x*mm_to_m;
	    transform.transform.translation.y = y*mm_to_m;
	    transform.transform.translation.z = z*mm_to_m;
	    transform.transform.rotation.x = 0;
	    transform.transform.rotation.y = 0;
	    transform.transform.rotation.z = 0;
	    transform.transform.rotation.w = 1;
	    tf_broadcaster.sendTransform(transform);
	}
