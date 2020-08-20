// '''this code uses Gstreamer'''

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Image.h>
#include <std_msgs/Header.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include <chrono> 

#include <signal.h>
void signal_handler(sig_atomic_t s) {
  std::cout << "You pressed Ctrl + C, exiting" << std::endl;
  exit(1);
}

using namespace std::chrono; 
using namespace std;
using namespace boost;

cv_bridge::CvImage img_bridge;
sensor_msgs::Image img_msg;
std_msgs::Header header;
int counter = 1;

// ROS parameter
int width, height, fps;
int white_balance, noise_reduction, edge_enhance;

double contrast, brightness, saturation;

/* --------------- notice ------------------- *//*

# for Webcam
camSet = 'v4l2src device=/dev/video0 ! video/x-raw, width=800, height=600, framerate=24/1 ! videoconvert ! appsink'

# for CSI (IMX 477)
camSet = "nvarguscamerasrc sensor-id=0 tnr-mode=1 wbmode=1 ! video/x-raw(memory:NVMM), width=1920, height=1080, framerate=30/1, format=NV12' ! nvvidconv flip-method=2 ! video/x-raw, width=1920, height=1080, format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink

#cam = cv2.VideoCapture(camSet)


// #when using other codec
// ''' test-> v4l2-ctl -d /dev/video1 --list-formats-ext '''
// # cam.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*'H264'))
// # cam.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*'MJPG'))
// # cam.set(cv2.CAP_PROP_FRAME_WIDTH, 1920);
// # cam.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080);
// # cap.set(cv2.CAP_PROP_FPS, 30);

*//* ------------------------------------------ */



string img_config(ros::NodeHandle nh){
    
    nh.param("cv_cam_node/width", width, 1920);
    nh.param("cv_cam_node/height", height, 1080);
    nh.param("cv_cam_node/fps", fps, 30);
    nh.param("cv_cam_node/white_balance", white_balance, 1);
    nh.param("cv_cam_node/noise_reduction", noise_reduction, 1);
    nh.param("cv_cam_node/edge_enhance", edge_enhance, 1);
    
    stringstream camSet;
    camSet << "nvarguscamerasrc sensor-id=0 tnr-mode=" << noise_reduction << " wbmode=" << white_balance << " ee-mode=" << edge_enhance << " ! video/x-raw(memory:NVMM), width=" << width << ", height=" << height << ", framerate=" << fps << "/1, format=NV12' ! nvvidconv flip-method=2 ! video/x-raw, width=" << width << ", height=" << height << ", format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink";  

    return camSet.str();
    
}




int main(int argc, char **argv){

	cout << "main start!! " << endl;
    
    ros::init(argc, argv, "cv_cam");
    ros::NodeHandle nh;
    ros::Publisher img_pub = nh.advertise<sensor_msgs::Image>("/imx477/image_raw", 100);
    ros::Rate rate(30);

    signal(SIGINT, signal_handler); // to exit program when ctrl+c

    // image set
    string camSet = img_config(nh);
    cv::VideoCapture cam(camSet); //, cv::CAP_GSTREAMER); 
    cam.set(CV_CAP_PROP_FOURCC, cv::VideoWriter::fourcc('H','2','6','4'));
    cam.set(CV_CAP_PROP_FRAME_WIDTH, width);
    cam.set(CV_CAP_PROP_FRAME_HEIGHT, height);
    cam.set(CV_CAP_PROP_FPS, fps);
    
    cv::Mat frame;   
	while (true){
        auto start = high_resolution_clock::now(); 
        cam >> frame;
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<microseconds>(stop - start);
        //ROS_INFO("row : %d col : %d time : %.2f", frame.rows, frame.cols, duration.count()/1000.0);
        
        header.seq = counter;
        header.stamp = ros::Time::now();
        img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::BGR8, frame);
        img_bridge.toImageMsg(img_msg); // from cv_bridge to sensor_msgs::Image
        img_pub.publish(img_msg);
        counter++;

        rate.sleep();
    }

	cam.release();
	cv::destroyAllWindows();

	return 0;
}
