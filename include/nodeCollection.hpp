// Author: Raul Cruz-Oliver
// Email: raul.cruz.oliver@gmail.com
// Date, place: January 2023, Butikkon, CH

#pragma once

// basic C++ ROS2 utilities
#include "rclcpp/rclcpp.hpp"

// joint_state message
#include "sensor_msgs/msg/joint_state.hpp"

// self made utilities to publish transform
#include "publishTransform.hpp"

class KRStatePublisher : public rclcpp::Node
{
	public:
		KRStatePublisher();

	private:
		rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr subscription_;

	private:
  		void KRJointsCallback(const sensor_msgs::msg::JointState::SharedPtr msg);
  
};

class KRStateManager : public rclcpp::Node
{
	public:
    	KRStateManager();

	private:
  		int count1_;
		int count2_;
    	bool increasing1_;
		bool increasing2_;
		rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr publisher_;
		rclcpp::TimerBase::SharedPtr timer_;
    	std::vector<std::string> joint_name_;

	private:
    	void timer_callback();

};

