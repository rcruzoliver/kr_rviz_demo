# Author: Raul Cruz-Oliver, rcruzoliver@student.ethz.ch
# Date, place : August 2023, Zurich

import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def static_transform(parent, child, position):
    return Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=[position[0], position[1], position[2], '0', '0', '0', parent, child]
        )

def generate_launch_description():
    # Define launch arguments
    urdf_file = os.path.join(get_package_share_directory('kr_rviz_demo'), 'urdf', 'kr2_robot_a810_tio_fixed.urdf')
    # botaSensor_position = ['0.070','-0.025','0.020']
    # accelerometer_position = ['0.050','-0.025','0.070']
    # nozzle_position = ['0','-0.025','-0.057']
    
    return LaunchDescription([
        DeclareLaunchArgument('use_sim_time', default_value='false',
                              description='Use simulation/Gazebo clock if true'),
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='screen',
            parameters=[{'use_sim_time': LaunchConfiguration('use_sim_time')}],
            arguments=[urdf_file]
        ),
        
        Node(
            package='kr_rviz_demo',          
            executable='state_publisher',
            name='state_publisher',
            arguments=["demo"],  
            output='screen',
        ),

        # static_transform('printhead', 'botaSensor', botaSensor_position),
        # static_transform('printhead', 'accelerometer', accelerometer_position),
        # static_transform('printhead', 'nozzle', nozzle_position),

        Node(
            package="rviz2",
            executable="rviz2",
            name="rviz2",
            output="screen",
            arguments=["-d", os.path.join(get_package_share_directory("kr_rviz_demo"), "rviz", "kr_rviz_demo.rviz")]
        )
    ])
