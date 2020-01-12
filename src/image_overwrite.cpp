#include "ros/ros.h"
#include <math.h>
#include "opencv2/opencv.hpp"
#include "sensor_msgs/Image.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <pthread.h>
#include "Labeling.h"

static const std::string WINDOW="image window";
static const std::string WINDOW2="processing";

pthread_mutex_t mutex;
sensor_msgs::Image raw_image;
cv_bridge::CvImagePtr cv_ptr;

void ImageCallback(const sensor_msgs::ImageConstPtr& msg){
	//ROS_INFO("I could receive !");
	try{
		cv_ptr=cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
	}
	catch(cv_bridge::Exception& e){
		ROS_ERROR("cv_bridge exception: %s",e.what());
		return;
	}
	
}

int main(int argc,char **argv){
	ros::init(argc,argv,"color_grouping");
	ros::NodeHandle n;
	ros::NodeHandle local_nh("~");
	image_transport::ImageTransport it(n);
	image_transport::Subscriber image_sub=it.subscribe("/raspi_cam/image_raw",1,&ImageCallback);
	image_transport::Publisher image_pub=it.advertise("/raspi_cam/overwritten",50);
	
	cv::Mat rawImage;
	cv::namedWindow(WINDOW);
	int w=640,h=480;
	short *mask2=new short[w*h];
	
	int H_min,H_max,S_min,S_max,V_min,V_max;
	int x1,x2,y1,y2;
	float xG,yG;
	
	ros::Rate loop_rate(20);
	
	cv::createTrackbar("Hmin",WINDOW,&H_min,255);
	cv::createTrackbar("Hmax",WINDOW,&H_max,255);
	cv::createTrackbar("Smin",WINDOW,&S_min,255);
	cv::createTrackbar("Smax",WINDOW,&S_max,255);
	cv::createTrackbar("Vmin",WINDOW,&V_min,255);
	cv::createTrackbar("Vmax",WINDOW,&V_max,255);
	
	while(ros::ok()){
		if(cv_ptr){
			rawImage=cv_ptr->image;
			cv::cvtColor(rawImage,hsv,CV_BGR2HSV);
			cv::inRange(hsv,cv::Scalar(H_min,S_min,V_min),cv::Scalar(H_max,S_max,V_max),masking);
			rectangle(masking,cv::Point(0,0),cv::Point(1,1),cv::Scalar(255),-1);
			labeling.Exec((uchar *)masking.data,mask2,w,h,true,30);
			ri=labeling.GetResultRegionInfo(0);
			ri->GetMin(x1,y1);
			ri->GetMax(x2,y2);
			ri->GetCenterOfGravity(xG,yG);
			ROS_INFO("GCenter: (%f,%f)",xG,yG);
			rectangle(rawImage,cv::Point(x1,y1),cv::Point(x2,y2),cv::Scalar(255,0,0),3);
			cv::imshow(WINDOW,masking);
			cv::imshow(WINDOW2,rawImage);
			cv::waitKey(3);
		}
		else{
			ROS_ERROR("failed to receive");
		}
		
		ros::spinOnce();
		loop_rate.sleep();
	}
	
	return 0;
	
}

