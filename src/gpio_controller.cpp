/**
 * This node controls Raspberrypi GPIO to send a command to STM controller.
 * Especially for control of direction of supporting device.
**/

/*
	STM  							RaspberryPi
	PB_13	----------	GPIO16
	PB_14	----------	GPIO20
	PC_4 	----------	GPIO21

				PB_13		PB_14		PC_4
	Up			1				1				0
	Down		1				0				1
	Right		0				1				0
	Left		0				0				1
	Stop		0				0				0
*/

#include <ros/ros.h>
#include <std_msgs/Char.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#define GPIO16 16
#define GPIO20 20
#define GPIO21 21

#define DEBUG

/** 
*/
char command='0';
bool changed=0;
char port[]="/dev/ttyACM0";
char data[10]={'0','0','0','0','0','0','0','0','0','0'};

void DirCommandCallBack(const std_msgs::Char &msg) {
	if(command!=msg.data){
		command=msg.data;
		changed=1;
	} else {
		changed=0;
	}
	command=msg.data;
  ROS_INFO_STREAM_ONCE("RECEIVED COMMAND !!");
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "gpio_controller");
  ros::NodeHandle n;
  ros::NodeHandle local_nh("~");

  ros::Subscriber command_sub = n.subscribe("/DirCommand", 10, DirCommandCallBack);
	ros::Rate loop_rate(10);

	if(wiringPiSetupGpio()==-1) return 1;
	fflush(stdout);

	pinMode(GPIO16,OUTPUT);
	pinMode(GPIO20,OUTPUT);
	pinMode(GPIO21,OUTPUT);
	digitalWrite(GPIO16,0);
	digitalWrite(GPIO20,0);
	digitalWrite(GPIO21,0);

	int fd=serialOpen(port,9600);
	/*if(fd<0){
		ROS_INFO(port,"%s cannot be opened");
	}*/

	while (ros::ok()) {
    ros::spinOnce();
		if(changed){
			switch(command){
			case 'u':
				digitalWrite(GPIO16,1);
				digitalWrite(GPIO20,1);
				digitalWrite(GPIO21,0);
				ROS_INFO("UP");
				break;
			case 'd':
				digitalWrite(GPIO16,1);
				digitalWrite(GPIO20,0);
				digitalWrite(GPIO21,1);
				ROS_INFO("DOWN");
				break;
			case 'r':
				digitalWrite(GPIO16,0);
				digitalWrite(GPIO20,1);
				digitalWrite(GPIO21,0);
				ROS_INFO("RIGHT");
				break;
			case 'l':
				digitalWrite(GPIO16,0);
				digitalWrite(GPIO20,0);
				digitalWrite(GPIO21,1);
				ROS_INFO("LEFT");
				break;
			default:
				digitalWrite(GPIO16,0);
				digitalWrite(GPIO20,0);
				digitalWrite(GPIO21,0);
				ROS_INFO("NONE");
				break;
				
			}
		}
		//serialPrintf(fd, data);
		//serialPutchar(fd,'0');
		//ROS_INFO("!!");
		loop_rate.sleep();
  }

	return 0;
}
