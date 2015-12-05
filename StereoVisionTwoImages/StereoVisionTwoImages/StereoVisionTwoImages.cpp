// StereoScopicTest.cpp


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
	while (true)
	{
		// Mats left and right images and for StereoBM
		Mat imgl, imgr, gl, gr;
		// Mats for the disparity results of StereoBM
		Mat disp, disp8;

		// Used for doing a disparity image with two offset images
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

		// Color the images as grayscale and store in gl and gr
		cvtColor(imgl, gl, CV_BGR2GRAY);
		cvtColor(imgr, gr, CV_BGR2GRAY);

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

		// Set StereoBM with gl and gr and store it in disp
		sbm(gl, gr, disp);
		normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);

		// Image of the original and disparity
		IplImage imgOL(imgl);
		IplImage imgOR(imgr);
		IplImage imgStereo(disp8);

		// Get distance using reprojectImageTo3D
		// XYZ is the object to contain all of 3D pixel information, will be used to calculate distance
		Mat XYZ;
		// Q is the object that holds all of the camera information needed for reprojectImageTo3D
		Mat Q;
		//**** Needs to be Revised/Implemented ****//
		// Creating the Q object does not work with the current camera that is used for this test
		// TODO
		//
		//stereoCalibration(...);
		//stereoRectify(...);
		//reprojectImageTo3D(disp8, XYZ, Q, false, CV_32F);

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