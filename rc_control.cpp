#include <ros/ros.h>
#include <iostream>
#include <mavros_msgs/RCIn.h>
#include <prometheus_msgs/ControlCommand.h>

#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <nav_msgs/Path.h>


#define NODE_NAME "rc_control"

using namespace std;

int channel = 0;

//即将发布的command
prometheus_msgs::ControlCommand Command_to_pub;

//发布
ros::Publisher swb_pub;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>　函数声明　<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void timerCallback();

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  回调函数  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void swb_c(const mavros_msgs::RCIn::ConstPtr &msg)
{
    channel = msg->channels[5];
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>　主函数　<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int main(int argc, char **argv)
{
    ros::init(argc, argv, "rc_control");
    ros::NodeHandle nh;

    swb_pub = nh.advertise<prometheus_msgs::ControlCommand>("/prometheus/control_command", 10);
    ros::Subscriber rc_sub = nh.subscribe<mavros_msgs::RCIn>("/mavros/rc/in", 100, swb_c);

    timerCallback();
    
	while(ros::ok())
    {
	    ros::spinOnce();
        
        if(channel > 1490 && channel < 1510)
        {
            Command_to_pub.header.stamp = ros::Time::now();
            Command_to_pub.Mode = prometheus_msgs::ControlCommand::Hold;
            Command_to_pub.Command_ID = Command_to_pub.Command_ID + 1;
            Command_to_pub.source = NODE_NAME;
            swb_pub.publish(Command_to_pub);
        }
        
        else if (channel > 1990 && channel < 2010)
        {
            Command_to_pub.header.stamp = ros::Time::now();
            Command_to_pub.Mode = prometheus_msgs::ControlCommand::Move;
            Command_to_pub.Command_ID = Command_to_pub.Command_ID + 1;
            Command_to_pub.source = NODE_NAME;
            Command_to_pub.Reference_State.Move_mode  = prometheus_msgs::PositionReference::XYZ_VEL;
            Command_to_pub.Reference_State.Move_frame = 0;
            Command_to_pub.Reference_State.time_from_start = -1;

            Command_to_pub.Reference_State.position_ref[0] = 0;
            Command_to_pub.Reference_State.position_ref[1] = 0;
            Command_to_pub.Reference_State.velocity_ref[0] = 0.1;
            Command_to_pub.Reference_State.velocity_ref[1] = 0;
            Command_to_pub.Reference_State.velocity_ref[2] = 0;
            swb_pub.publish(Command_to_pub);
        }
        else if (channel > 990 && channel < 1010)
        {
                        Command_to_pub.header.stamp = ros::Time::now();
            Command_to_pub.Mode = prometheus_msgs::ControlCommand::Move;
            Command_to_pub.Command_ID = Command_to_pub.Command_ID + 1;
            Command_to_pub.source = NODE_NAME;
            Command_to_pub.Reference_State.Move_mode  = prometheus_msgs::PositionReference::XYZ_VEL;
            Command_to_pub.Reference_State.Move_frame = 0;
            Command_to_pub.Reference_State.time_from_start = -1;

            Command_to_pub.Reference_State.position_ref[0] = 0;
            Command_to_pub.Reference_State.position_ref[1] = 0;
            Command_to_pub.Reference_State.velocity_ref[0] = -0.1;
            Command_to_pub.Reference_State.velocity_ref[1] = 0;
            Command_to_pub.Reference_State.velocity_ref[2] = 0;
            swb_pub.publish(Command_to_pub);
        }
        

    }
    return 0;
}

void timerCallback()
{
    cout << ">>>>>>>>>>>>>>>> Welcome to use Prometheus RC Control <<<<<<<<<<<<<<<<"<< endl;
    cout << endl;
    cout << ">>>Make sure to go into Offboard mode before using the SWB channel<<<<" <<endl;
    cout << endl;
    cout << ">>>>>>>>>>>>>>>>>>>>>>>  SWB上位----Vx = 0.1 m/s.  <<<<<<<<<<<<<<<<<<<<" <<endl;
    cout << ">>>>>>>>>>>>>>>>>>>>>>>  SWB中位----Hold.  <<<<<<<<<<<<<<<<<<<<<<<<<<<<" <<endl;
    cout << ">>>>>>>>>>>>>>>>>>>>>>>  SWB下位----Vx = 0.1 m/s.  <<<<<<<<<<<<<<<<<<<<" <<endl;
}