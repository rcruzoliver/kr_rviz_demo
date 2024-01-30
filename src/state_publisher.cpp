// Author: Raul Cruz-Oliver
// Date, place: Novemeber 2023, Butikkon, CH

#include "tf_publisher_demo_cartesian.h"

int main(int argc, char * argv[])
{
	rclcpp::init(argc, argv);

	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << "[demo]" << std::endl;
		return 1;
	}

	std::string option = argv[1];

	if (option == "demo") {
		std::cout << "State publisher for demo cartesian robot has started." << std::endl;
	} else {
		std::cerr << "Invalid option. Use 'demo' argument to start the demostration example." << std::endl;
	}

	if (option == "demo") {
		// rclcpp::spin(std::make_shared<DemoCartesianPositionSubscriber>());
		rclcpp::spin(std::make_shared<MinimalPublisher>());
	} else {
		return 1;
	}

	rclcpp::shutdown();
	return 0;
}
