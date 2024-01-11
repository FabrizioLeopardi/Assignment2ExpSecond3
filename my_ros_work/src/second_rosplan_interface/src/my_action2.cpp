#include "second_rosplan_interface/my_action2.h"
#include "geometry_msgs/Twist.h"
#include <unistd.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <assignment_2_2022/PlanningAction.h>
#include <assignment_2_2022/PlanningActionResult.h>

//ros::Publisher pub;
ros::Subscriber sub_res;
int current_marker_goal = 0;
int ids[4];
int current=0;
bool goal_set_ = false;

namespace KCL_rosplan {

	MyActionInterface::MyActionInterface(ros::NodeHandle &nh) {

	}

	bool MyActionInterface::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) {

		double x[5];
		double y[5];
		x[0]=1.0;
		y[0]=1.0;
		x[1]=6.0;
		y[1]=2.0;
		x[2]=7.0;
		y[2]=-5.0;
		x[3]=-3.0;
		y[3]=-8.0;
		x[4]=-7.0;
		y[4]=1.5;

		//char c = msg->name.c_str()[0];
		//if(c=='g')
		//{
			int wp_target = msg->parameters[2].value[2] - '0';
			//std::cout << wp_target << std::endl;
			actionlib::SimpleActionClient<assignment_2_2022::PlanningAction> ac("reaching_goal",true);
			if (goal_set_ == true)
			{
				std::cout << "Cancel previous goals" << std::endl;
				ac.cancelAllGoals();
				goal_set_=false;
			}
			assignment_2_2022::PlanningGoal goal;
			ac.waitForServer();
			goal.target_pose.pose.position.x=x[wp_target];
			goal.target_pose.pose.position.y=y[wp_target];
			ac.sendGoal(goal);
			goal_set_=true;
			ac.waitForResult();
			//sleep(20);
		//}
		
		/*
		if(c=='s')
		{
			bool rotate = true;
			while (rotate)
			{
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
			}
			++current_marker_goal;
			//sleep(20);

		}
		*/
		//ROS_INFO("Action (%s) performet: completed!", msg->name.c_str());
		return true;
	}

}

void goal_callback(const assignment_2_2022::PlanningActionResult::ConstPtr& data)
{
	if (data->status.status == 2 or data->status.status == 3)
		goal_set_=false;
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "my_rosplan_action", ros::init_options::AnonymousName);
	ids[0]=11;
	ids[1]=12;
	ids[2]=13;
	ids[3]=15;
	ros::NodeHandle nh("~");
	//pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1000);
	sub_res = nh.subscribe("/reaching_goal/result",1000,goal_callback);
	KCL_rosplan::MyActionInterface my_aci(nh);
	my_aci.runActionInterface();
	return 0;
}
