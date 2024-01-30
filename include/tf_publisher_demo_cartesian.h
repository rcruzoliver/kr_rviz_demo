// Author: Raul Cruz-Oliver
// Date, place: November 2023, Butikkon, CH

#include "publishTransform.h"
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class DemoCartesianPositionSubscriber : public rclcpp::Node
{
public:
  DemoCartesianPositionSubscriber(): Node("ctrlx_middleware")
  {
  
  // subscription_ = this->create_subscription<geometry_msgs::msg::PoseStamped>( "beckhoff/position", 10, std::bind(&DemoCartesianPositionSubscriber::handle_position, this, std::placeholders::_1));
      
  // subscription_ = this->create_subscription<geometry_msgs::msg::Point>("pose_cartesian", 10, std::bind(&DemoCartesianPositionSubscriber::handle_position, this, std::placeholders::_1));
  }

private:
	const double z_offset_carriage_x_to_base_x = 20; // in mm
	const double z_offset_y_base_to_carriage_y = 10; // in mm
	const double y_offset_z_carriage_to_base_z = -20; // in mm

  // void handle_position(const geometry_msgs::msg::Point::SharedPtr msg)
  void handle_position()
  {
  	// geometry_msgs::msg::PoseStamped::SharedPtr // for a PoseStampedMessage (change also in the constructor ;) )
  
	tf2_ros::TransformBroadcaster tf_broadcaster(this);

	// Read the position data (if it comes from a PoseStamped Message https://docs.ros.org/en/noetic/api/geometry_msgs/html/msg/PoseStamped.html)
	// auto position_data_x = msg->pose.position.x;
	// auto position_data_y = msg->pose.position.y;
	//auto position_data_z = msg->pose.position.z;
	
	// Read the position data (if it comes from a Point Message https://docs.ros.org/en/melodic/api/geometry_msgs/html/msg/Point.html)
	// auto position_data_x = msg->x;
	// auto position_data_y = msg->y;
	// auto position_data_z = msg->z;

	publishTransform("base", "link1", 0, 0, 0, tf_broadcaster, *this); 
	publishTransform("link1", "linkJ2", 0, 0, 0, tf_broadcaster, *this); 
	publishTransform("linkJ2", "link2", 0, 0, 0, tf_broadcaster, *this); 
	publishTransform("link2", "link3", 0, 0, 0, tf_broadcaster, *this); 
	publishTransform("link3", "linkJ4", 0, 0, 0, tf_broadcaster, *this); 
	publishTransform("linkJ4", "link4", 0, 0, 0, tf_broadcaster, *this); 
	publishTransform("link4", "link5", 0, 0, 0, tf_broadcaster, *this); 
	publishTransform("link5", "linkJ6", 0, 0, 0, tf_broadcaster, *this); 
	publishTransform("linkJ6", "link6", 0, 0, 0, tf_broadcaster, *this); 
	publishTransform("link6", "end_effector", 0, 0, 0, tf_broadcaster, *this); 
	publishTransform("end_effector", "link1", 0, 0, 0, tf_broadcaster, *this); 

  }

  rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr subscription_;
};

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("minimal_publisher"), count_(0)
    {
      publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
      timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

  private:

    void timer_callback()
    {
      auto message = std_msgs::msg::String();
      message.data = "Hello, world! " + std::to_string(count_++);
      // RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      publisher_->publish(message);

	  // tf2_ros::TransformBroadcaster tf_broadcaster(this);
	  // publishTransform("base", "link1", 0, 0, 0, tf_broadcaster, *this); 
	  // publishTransform("link1", "linkJ2", 0, 0, 0, tf_broadcaster, *this); 
	  // publishTransform("linkJ2", "link2", 0, 0, 0, tf_broadcaster, *this); 
	  // publishTransform("link2", "link3", 0, 0, 0, tf_broadcaster, *this); 
	  // publishTransform("link3", "linkJ4", 0, 0, 0, tf_broadcaster, *this); 
	  // publishTransform("linkJ4", "link4", 0, 0, 0, tf_broadcaster, *this); 
	  // publishTransform("link4", "link5", 0, 0, 0, tf_broadcaster, *this); 
	  // publishTransform("link5", "linkJ6", 0, 0, 0, tf_broadcaster, *this); 
	  // publishTransform("linkJ6", "link6", 0, 0, 0, tf_broadcaster, *this); 
	  // publishTransform("link6", "end_effector", 0, 0, 0, tf_broadcaster, *this); 
	  // publishTransform("end_effector", "link1", 0, 0, 0, tf_broadcaster, *this); 
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};