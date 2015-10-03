# OpenCV 

-- Tutorial to setup OpenCV with Visual Studio
http://opencv-srf.blogspot.com/2013/05/installing-configuring-opencv-with-vs.html

-- Visual Studio "Additional Included Directories" for Configuration Properties : C/C++ : General
$(OPENCV_DIR)\include;%(AdditionalIncludeDirectories)

-- Visual Studio "Additional Included Directories" for Configuration Properties : Linker : General
$(OPENCV_DIR)\x86\vc11\lib;%(AdditionalIncludeDirectories)

-- Visual Studio "Additional Dependencies" for Configuration Properties : Linker : Input
opencv_calib3d2410.lib
opencv_calib3d2410d.lib
opencv_contrib2410.lib
opencv_contrib2410d.lib
opencv_core2410.lib
opencv_core2410d.lib
opencv_features2d2410.lib
opencv_features2d2410d.lib
opencv_flann2410.lib
opencv_flann2410d.lib
opencv_gpu2410.lib
opencv_gpu2410d.lib
opencv_highgui2410.lib
opencv_highgui2410d.lib
opencv_imgproc2410.lib
opencv_imgproc2410d.lib
opencv_legacy2410.lib
opencv_legacy2410d.lib
opencv_ml2410.lib
opencv_ml2410d.lib
opencv_nonfree2410.lib
opencv_nonfree2410d.lib
opencv_objdetect2410.lib
opencv_objdetect2410d.lib
opencv_ocl2410.lib
opencv_ocl2410d.lib
opencv_photo2410.lib
opencv_photo2410d.lib
opencv_stitching2410.lib
opencv_stitching2410d.lib
opencv_superres2410.lib
opencv_superres2410d.lib
opencv_ts2410.lib
opencv_ts2410d.lib
opencv_video2410.lib
opencv_video2410d.lib
opencv_videostab2410.lib
opencv_videostab2410d.lib