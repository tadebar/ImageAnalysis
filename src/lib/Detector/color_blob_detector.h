//	color_blob_detector.h
//	Defines the color blob detector class
//	Troy Adebar
//	copyright 2018
//	troy.adebar@gmail.com

#ifndef COLOR_BLOB_DETECTOR_H
#define COLOR_BLOB_DETECTOR_H

#include "opencv2/opencv.hpp"
#include "detector.h"

using namespace cv;

class ColorBlobDetector : Detector
{
public:
	ColorBlobDetector();
	~ColorBlobDetector() {}
	
	int init();

	int detect(const Mat& img, unsigned int& numDetected, std::vector<Point2f>& center, std::vector<Rect>& boundingBox);

	void setMinimumBlobSize(int size) { minimumBlobSize_ = size; }
	void addRange(const Scalar& lowerLimit, const Scalar& upperLimit);

private:

	int convertToHSV(const Mat& bgr);
	int thresholdInput();

	void resetThresholding();

	Mat inputImageHSV_;

	std::vector<Scalar> upperLimitHSV_;
	std::vector<Scalar> lowerLimitHSV_;
	Mat inRangeImage_;
	int minimumBlobSize_;
};


#endif  // COLOR_BLOB_DETECTOR_H