// StereoScopicTest.cpp : Defines the entry point for the console application.
// http://stackoverflow.com/questions/23643813/opencv-stereo-vision-depth-map-code-does-not-work


#include "stdafx.h"

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/contrib/contrib.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

	// Capture the video from the webcam
	// 0 - webcam, 1 - external video feed
	VideoCapture cap(1); 

	// If there's no video capture, exit program
	if (!cap.isOpened())  
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	// Loop and get constant feed of the original video feed
	// and the disparity.
	while (true)
	{
		// Mats Used
		Mat imgOriginal, imgl, imgr, g1, g2;
		Mat disp, disp8;

		// Check if imgOriginal (camera feed) can read a new frame
		bool bSuccess = cap.read(imgOriginal);

		// If not successful, break loop
		if (!bSuccess)
		{
			cout << "cannot read a frame from video stream" << endl;
			break;
		}

		// TEST IMAGES
		// Used for doing a disparity image with two offset images
		// Uncomment the cvtColor to test images and comment the camera feed
		/*imgl = cvLoadImage(argv[1]);
		imgr = cvLoadImage(argv[1]);*/
		/*cout << "Arguments:" << endl;
		cout << argv[1] << " " << argv[2] << endl;*/

		// Resize imgl and imgr
		/*Size size(384, 288);
		resize(imgl, imgl, size);
		resize(imgr, imgr, size);*/

		// Error if images are not read
		/*if (!imgl.data || !imgr.data)
		{
			if (!imgl.data && !imgr.data)
				cout << "Couldn't find imgl and imgr" << endl;
			else if (!imgl.data)
				cout << "Couldn't find imgl" << endl;
			else
				cout << "Couldn't find imgr" << endl;
			return -1;
		}*/

		/*cvtColor(imgl, g1, CV_BGR2GRAY);
		cvtColor(imgr, g1, CV_BGR2GRAY);*/

		// TEST CAMERA FEED
		// Used for doing a disparity image from single webcam feed
		// Sets the color of the camera and store it into g1/g2
		cvtColor(imgOriginal, g1, CV_BGR2GRAY);
		cvtColor(imgOriginal, g2, CV_BGR2GRAY);

		// StereoBM
		// Use StereoBM to create disparity image
		StereoBM sbm;
		sbm.state->SADWindowSize = 9;//9;
		sbm.state->numberOfDisparities = 112;
		sbm.state->preFilterSize = 5;
		sbm.state->preFilterCap = 61;
		sbm.state->minDisparity = -39;
		sbm.state->textureThreshold = 507;
		sbm.state->uniquenessRatio = 0;
		sbm.state->speckleWindowSize = 0;
		sbm.state->speckleRange = 4;// 8;
		sbm.state->disp12MaxDiff = 1;

		// Set StereoBM with g1 and g2 and store it in disp
		sbm(g1, g2, disp);
		normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);

		// Image of the original
		/*IplImage imgOL(imgl);
		IplImage imgOR(imgr);*/
		IplImage imgO(imgOriginal);
		// Image of the disparity
		IplImage imgStereo(disp8);
		/*cvShowImage("Original Left", &imgOL);
		cvShowImage("Original Right", &imgOR);*/
		cvShowImage("Original Image", &imgO);
		cvShowImage("Stereo Vision", &imgStereo);

		// Exit loop by pressing the 'esc' key
		if (waitKey(30) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;
}