////////////////////////////////////////////////////////////////////////
//
// WebcamStream.cpp
//
// This is a simple, introductory OpenCV program. The program reads frames 
// from the webcam and displays. 
//
////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "opencv2/opencv.hpp"
#include "color_blob_detector.h"

using namespace std;
using namespace cv;

int main(int, char**)
{
	cout << "Starting." << endl;

	VideoCapture cap;

	if (!cap.open(1))
	{
		cout << "Failed to open" << endl;
		waitKey(1000);
		return -1;
	}

	if (!cap.isOpened())
	{
		cout << "Error opening video stream or file" << endl;
		waitKey(1000);
		return -1;
	}

	Mat frame;

	ColorBlobDetector detector;
	detector.setMinimumBlobSize(1500);
	detector.addRange(Scalar(0, 100, 100), Scalar(75, 255, 255));
	detector.addRange(Scalar(150, 100, 100), Scalar(180, 255, 255));
	//detector.addRange(Scalar(0, 100, 100), Scalar(20, 255, 255));
	//detector.addRange(Scalar(160, 100, 100), Scalar(170, 255, 255));


	namedWindow("Tracked Red Ball", 1);

	while (1)
	{
		cap >> frame;
		
		if (frame.empty())
		{
			cout << "Empty frame" << endl;
			break;
		}

		unsigned int numDetected;
		std::vector<Point2f> center;
		std::vector<Rect> boundingBox;

		detector.detect(frame, numDetected, center, boundingBox);
				
		for (unsigned int i = 0; i < numDetected; ++i)
		{
			rectangle(frame, boundingBox.at(i), Scalar(0, 255, 0));
		}
	
		imshow("Tracked Red Ball", frame);

		if (0 <= waitKey(1) )
		{
			break;
		}
	}
	
	cout << "Releasing" << endl;

	cap.release();

	waitKey(2000);

	cout << "Quitting" << endl;
	return 0;
}