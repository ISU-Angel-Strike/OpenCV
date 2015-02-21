#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;
char key;

int main() {
	cvNamedWindow("Camera Output", 1);
	CvCapture *capture = cvCaptureFromCAM(CV_CAP_ANY);

	while (1) {
		IplImage *frame = cvQueryFrame(capture);
		cvShowImage("Camera Output", frame);
		key = cvWaitKey(10);
		if (char(key) == 27)
			break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("Camera Output");

	return 0;
}