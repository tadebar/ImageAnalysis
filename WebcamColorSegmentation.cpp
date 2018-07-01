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

using namespace std;
using namespace cv;

int main(int, char**)
{
	cout << "Starting." << endl;

	VideoCapture cap;

	if (!cap.open(0))
	{
		cout << "Failed to open" << endl;
		waitKey(0);
		return -1;
	}

	if (!cap.isOpened())
	{
		cout << "Error opening video stream or file" << endl;
		return -1;
	}

	Mat frame;

	namedWindow("Tracked Red Ball", 1);

	while (1)
	{
		cap >> frame;
		
		if (frame.empty())
		{
			cout << "Empty frame" << endl;
			break;
		}

		Mat hsvImage;
		cvtColor(frame, hsvImage, COLOR_BGR2HSV);
		
		// Threshold the HSV image, keep only the red pixels
		Mat inLowerRedHueRange;
		Mat inUpperRedHueRange;
		inRange(hsvImage, Scalar(0, 100, 100), Scalar(20, 255, 255), inLowerRedHueRange);
		inRange(hsvImage, Scalar(160, 100, 100), Scalar(170, 255, 255), inUpperRedHueRange);
		
		// Combine the above two images
		Mat inRedHueRange;
		addWeighted(inLowerRedHueRange, 1.0, inUpperRedHueRange, 1.0, 0.0, inRedHueRange);
		
		int largest_area = 0;
		int largest_contour_index = 0;

		vector< vector<Point> > contours;
		vector<Vec4i> hierarchy;

		findContours(inRedHueRange, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE); // Find the contours in the image
		
		for (int i = 0; i< contours.size(); i++) 
		{// iterate through each contour. 
			double a = contourArea(contours[i], false);  //  Find the area of contour
			if (a>largest_area) 
			{
				largest_area = a;
				largest_contour_index = i;                //Store the index of largest contour
														  //bounding_rect=boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
			}
		}

		vector<Moments> mu(contours.size());
		for (int i = 0; i < contours.size(); i++)
		{
			mu[i] = moments(contours[i], false);
		}

		vector<Point2f> mc(contours.size());
		for (int i = 0; i < contours.size(); i++)
		{
			mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		}

		
		if (contours.size() > 0 && mu[largest_contour_index].m00 > 1500)
		{
			//drawContours(frame, contours, largest_contour_index, Scalar(0, 255, 0), LINE_4, 8, hierarchy); // Draw the largest contour using previously stored index.
			Rect box = boundingRect(contours[largest_contour_index]);
			rectangle(frame, box, Scalar(0, 255, 0));
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