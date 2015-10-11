// StereoScopicTest.cpp : Defines the entry point for the console application.
// http://stackoverflow.com/questions/23643813/opencv-stereo-vision-depth-map-code-does-not-work


#include "stdafx.h"

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	VideoCapture cap(0); //capture the video from web cam

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	

	////changed it to cvNamedWindow
	//cvNamedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	//int iLowH = 0;
	//int iHighH = 179;

	//int iLowS = 0;
	//int iHighS = 255;

	//int iLowV = 0;
	//int iHighV = 255;

	////Create trackbars in "Control" window, Settings set to detect a hue of RED
	//cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	//cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	//cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	//cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	//cvCreateTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
	//cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	int i = 0;
	while (true)
	{
		Mat imgOriginal, g1, g2;
		Mat disp, disp8;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;

		//// Image of the using the Camera
		//IplImage imgStereo(imgOriginal);

		//// Image of the original
		//IplImage imgO(imgOriginal);

		//cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
		cvtColor(imgOriginal, g1, CV_BGR2GRAY);
		cvtColor(imgOriginal, g2, CV_BGR2GRAY);

		// StereoBM
		StereoBM sbm;
		sbm.state->SADWindowSize = 9;
		sbm.state->numberOfDisparities = 112;
		sbm.state->preFilterSize = 5;
		sbm.state->preFilterCap = 61;
		sbm.state->minDisparity = -39;
		sbm.state->textureThreshold = 507;
		sbm.state->uniquenessRatio = 0;
		sbm.state->speckleWindowSize = 0;
		sbm.state->speckleRange = 8;
		sbm.state->disp12MaxDiff = 1;

		sbm(g1, g2, disp);
		normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);

		//imshow("Original", imgOriginal); //show the original image
		//imshow("Stereo Vision", disp8); //show the stereo image

		//use cvShowImage instead of imshow
		// Image of the using the Camera
		IplImage imgStereo(disp8);
		// Image of the original
		IplImage imgO(imgOriginal);
		cvShowImage("Original", &imgO);
		cvShowImage("Stereo Vision", &imgStereo);

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
		i++;
	}

	return 0;
}