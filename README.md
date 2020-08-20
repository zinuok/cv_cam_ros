# cv_cam_ros

***
setting guide for Nvidia Xavier NX (arm architecture)
# Index
### 0. OpenCV (ver. 3.4.1) install 
### 1. Intel Realsense camera: D435i
### 2. CSI camera: IMX477
### 3. Teamviewer for arm-architecture
***
<br><br>

## 0. OpenCV (ver. 3.4.1) install 
from [engcang](https://github.com/engcang/vins-application#-opencv-with-cuda--necessary-for-gpu-version-1)
+ for Xavier NX, CUDA_ARCH_BIN = 7.2 
+ when patch using **test.patch**
```
$ mv test.patch ~<opencv directory>/opencv-3.4.1/modulest/core/include/opencv2/core/
$ patch -N cvdef.h test.patch
```

## 1. Intel Realsense camera: D435i
from [IntelRealSense](https://github.com/IntelRealSense/librealsense/blob/master/doc/installation.md)
+ **my version info**
    + SDK - 2.36.0
    + Firmware: 5.12.6.0


+ **Download the complete source tree with git**
```
$ git clone https://github.com/IntelRealSense/librealsense.git
```

+ **Download and unzip the latest stable version from [here](https://github.com/IntelRealSense/librealsense/releases)**

+ **unzip**
