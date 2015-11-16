# RGBD Sync SDK - Drawing Documentation

## RGBD Sync SDK

This project and the Drawing repository are subparts of the RGBD Sync SDK. 
This SDK is design for file access to data (robot information, depth, infrared, video, bodies and faces from a Kinect2, ...) and easy way to read them synchronously
from separate sources almost like in ROS bag. 

The RGBD Sync SDK has been use to record the [MobileRGBD corpus](http://MobileRGBD.inrialpes.fr/). It is available for people who want
to work on this corpus, and anyone who need to use it within the term of the LICENCE.

## Drawing

The classes from the Drawing repository are intended to read data from the [MobileRGBD corpus](http://MobileRGBD.inrialpes.fr/) and/or draw the in cv::Mat object from [OpenCV](http://opencv.org/).
They can be used to draw directly data from the Kinect2 device: video, depth, infrared, skeletons (aka body in Kinect2) and faces.

## Participate!

You can help us finding bugs, proposing new functionalities and more directly on this website! Click on the "New issue" button in the menu to do that.
You can browse the git repository here on GitHub, submit patches and push requests!

## Licensing

RGBD Sync SDK and submodules are free software; you can redistribute and/or modify them under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.
[Consult the licence on the FSF website](http://www.gnu.org/licenses/lgpl-3.0.txt).

If you are a researcher and this software helps you, please cite our publication on MobileRGBD:  
+ *MobileRGBD, An Open Benchmark Corpus for mobile RGB-D Related Algorithms*, Dominique Vaufreydaz, Amaury N&egrave;gre,
13th International Conference on Control, Automation, Robotics and Vision, Dec 2014, Singapore, 2014. [(go to author version)](https://hal.inria.fr/hal-01095667)

Copyright (c) 2015, University of Grenoble Alpes and Inria, All rights reserved.
Dominique Vaufreydaz <dominique.vaufreydaz@inria.fr> 

