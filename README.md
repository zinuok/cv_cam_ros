# cv_cam_ros

***
ROS package read live images from CSI camera and publish ROS sensor image topic, using OpenCV 3.4.1 and gstreamer.<br>
+ **camera:** IMX477 HQ RPI V1.0 (any CSI camera using gstramer will be available, but not tested yet) 
+ **image topic name:** /imx477/image_raw
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

## Parameters in launch file
+ width: image width
+ height: image height
+ fps: image frame per second
<br>
+ white_balance: control white balance  => 0:off, 1:auto(default)
+ noise_reduction: controll image noise => 0:off, 1:Fast(default), 2:High Quality
+ edge_enhance: control contour         => 0:off, 1:Fast(default), 2:High Quality

<br><br>
For image (width, height, fps), possible combinations of values are set by gstreamer.<br>
ex) (width, height, fps) = (1920, 1080, 30)   (640, 480, 30)  etc..
