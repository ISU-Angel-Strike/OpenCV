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

	// Loop and get constant feed of the original video feed
	// and the disparity.
	while (true)
	{
		// Mats Used
		Mat imgl, imgr, g1, g2;
		Mat disp, disp8;

		// Used for doing a disparity image with two offset images
		// Uncomment the cvtColor to test images and comment the camera feed
		imgl = cvLoadImage(argv[7]);
		imgr = cvLoadImage(argv[8]);
		/*cout << "Arguments:" << endl;
		cout << argv[1] << " " << argv[2] << endl;*/

		// Error if images are not read
		if (!imgl.data || !imgr.data)
		{
			if (!imgl.data && !imgr.data)
				cout << "Couldn't find imgl and imgr" << endl;
			else if (!imgl.data)
				cout << "Couldn't find imgl" << endl;
			else
				cout << "Couldn't find imgr" << endl;
			return -1;
		}

		cvtColor(imgl, g1, CV_BGR2GRAY);
		cvtColor(imgr, g2, CV_BGR2GRAY);

		// StereoBM
		// Use StereoBM to create disparity image
		StereoBM sbm;
		sbm.state->SADWindowSize = 5;//9;
		sbm.state->numberOfDisparities = 112;//48;//112
		sbm.state->preFilterSize = 5;//5
		sbm.state->preFilterCap = 61;//61
		sbm.state->minDisparity = -39;//-39
		sbm.state->textureThreshold = 507;//507
		sbm.state->uniquenessRatio = 5;//15;
		sbm.state->speckleWindowSize = 0;//0
		sbm.state->speckleRange = 8;// 8;
		sbm.state->disp12MaxDiff = 1;//1

		// Set StereoBM with g1 and g2 and store it in disp
		sbm(g1, g2, disp);
		normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);

		// StereoSGBM
		/*StereoSGBM sgbm;
		sgbm.SADWindowSize = 5;
		sgbm.numberOfDisparities = 192;
		sgbm.preFilterCap = 4;
		sgbm.minDisparity = -64;
		sgbm.uniquenessRatio = 1;
		sgbm.speckleWindowSize = 150;
		sgbm.speckleRange = 2;
		sgbm.disp12MaxDiff = 10;
		sgbm.fullDP = false;
		sgbm.P1 = 600;
		sgbm.P2 = 2400;*/

		// Set StereoSGBM with g1 and g2 and store it in disp
		/*sgbm(g1, g2, disp);
		normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);*/

		// Image of the original and disparity
		IplImage imgOL(imgl);
		IplImage imgOR(imgr);
		IplImage imgStereo(disp8);

		// Save the imgStereo image
		//vector<int> compression;
		//compression.push_back(CV_IMWRITE_PNG_COMPRESSION);
		//compression.push_back(9);
		//imwrite("QuadStereo.png", disp8, compression);

		// Show images
		cvShowImage("Original Left", &imgOL);
		cvShowImage("Original Right", &imgOR);
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