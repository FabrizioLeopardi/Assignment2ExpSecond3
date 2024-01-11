#include "my_rosplan_interface/my_action.h"
#include "geometry_msgs/Twist.h"
#include <unistd.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <assignment_2_2022/PlanningAction.h>
#include <my_rosplan_interface/Marker.h>
#include <geometry_msgs/PoseStamped.h>

ros::Publisher pub;
ros::Subscriber sub;
int current_marker_goal = 0;
int ids[4];
int current=0;

namespace KCL_rosplan {

	MyActionInterface::MyActionInterface(ros::NodeHandle &nh) {

	}

	bool MyActionInterface::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) {

			std::cout << "FLAG2: searchfor_marker" << std::endl;
			bool rotate = true;
			while (rotate)
			{
				//std::cout << "try11" << std::endl;
				geometry_msgs::Twist msgT;
				msgT.angular.z = 1.0;
				//pub.publish(msgT);
				//std::cout << current << std::endl;
				//std::cout << ids[current_marker_goal] << std::endl;
				if (current == ids[current_marker_goal])
				{
					rotate = false;
					msgT.angular.z=0.0;
					std::cout << "Ok, maker seen!" << std::endl;
				}
				pub.publish(msgT);
				ros::spinOnce();
			}
			++current_marker_goal;
			//if (c=='g')
			//	std::cout << "FLAG" << std::endl;
			//sleep(20);

		//}
		//ROS_INFO("Action (%s) performet: completed!", msg->name.c_str());
		return true;
	}

}

void my_callback(const my_rosplan_interface::Marker::ConstPtr& msg)
{
	//std::cout << "OK, seen!" << std::endl;
	if (msg->id == ids[current_marker_goal])
		current = msg->id;
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "my_rosplan_action", ros::init_options::AnonymousName);
	ids[0]=11;
	ids[1]=12;
	ids[2]=13;
	ids[3]=15;
	ros::NodeHandle nh("~");
	pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1000);
	sub = nh.subscribe("/marker_pub",1000,my_callback);
	KCL_rosplan::MyActionInterface my_aci(nh);
	my_aci.runActionInterface();
	return 0;
}
