# cv_cam_ros

***
ROS package read image from CSI camera and publish ROS sensor image topic, using OpenCV 3.4.1 and gstreamer.<br>
+ camera: IMX477 HQ RPI V1.0 (any CSI camera using gstramer will be available, but not tested yet) 
+ image topic name: /imx477/image_raw
***
<br><br>

## Build
```
$ git clone https://github.com/zinuok/cv_cam_ros.git
$ cd ~/catkin_ws
$ catkin build cv_cam
$ source ~/catkin_ws/devel/setup.bash
```

## Run
```
$ roslaunch cv_cam cv_cam.launch
```

## Parameter launch file


