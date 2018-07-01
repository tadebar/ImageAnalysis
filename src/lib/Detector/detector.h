//	detector.h
//	Defines the object detector interface
//	Troy Adebar
//	copyright 2018
//	troy.adebar@gmail.com

#ifndef DETECTOR_H
#define DETECTOR_H

#include "opencv2/opencv.hpp"

using namespace cv;

class Detector 
{
public:
	virtual ~Detector() {}

	// Initialize the detector
	virtual int init() = 0;

	// Detect an object
	// parameters:
	// img (input) - the input image
	// numDetected (output) - the number of detected objects in img
	// center (output) - vector of object centers of seize numDetected
	// pos (output) - vector of object bounding boxes of size numDetected
	// returns 0 if successful 
	virtual int detect(const Mat& img, unsigned int& numDetected, std::vector<Point2f>& center, std::vector<Rect>& boundingBox) = 0;
};


#endif  // DETECTOR_H