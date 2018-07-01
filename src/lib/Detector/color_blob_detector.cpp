//	color_blob_detector.cpp
//	Defines the color blob detector class
//	Troy Adebar
//	copyright 2018
//	troy.adebar@gmail.com

#include "color_blob_detector.h"
#include "image_analysis_constants.h"

using namespace cv;


ColorBlobDetector::ColorBlobDetector() :
	minimumBlobSize_(std::numeric_limits<int>::max())
{
	upperLimitHSV_.clear();
	lowerLimitHSV_.clear();
}


int ColorBlobDetector::init()
{
	resetThresholding();

	return OK;
}

int ColorBlobDetector::detect(const Mat& img, unsigned int& numDetected, std::vector<Point2f>& center, std::vector<Rect>& boundingBox)
{
	numDetected = 0;
	center.clear();
	boundingBox.clear();

	resetThresholding();

	if (OK != convertToHSV(img))
	{
		std::cout << "Error converting to HSV" << std::endl;
		return ERROR;
	}
		
	if (OK != thresholdInput())
	{
		std::cout << "Error thresholding input" << std::endl;
		return ERROR;
	}

	std::vector< std::vector<Point> > contours;
	std::vector<Vec4i> hierarchy;

	// Find the contours in the image
	findContours(inRangeImage_, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE); 

	for (int i = 0; i< contours.size(); i++)
	{
		double a = contourArea(contours[i], false); 
		if (a > minimumBlobSize_)
		{
			Moments mu = moments(contours[i], false);
			Point2f mc = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00); 
			Rect bbox = boundingRect(contours[i]);

			numDetected++;
			center.push_back(mc);
			boundingBox.push_back(bbox);
		}
	}

	return OK;
}

int ColorBlobDetector::convertToHSV(const Mat& bgr)
{
	cvtColor(bgr, inputImageHSV_, COLOR_BGR2HSV);

	return OK;
}

void ColorBlobDetector::resetThresholding()
{
	inRangeImage_.release();
}

int ColorBlobDetector::thresholdInput()
{
	// upper and lower limits must be same length and it must be non-zero 
	if (upperLimitHSV_.size() != lowerLimitHSV_.size() || upperLimitHSV_.size() == 0)
	{
		return ERROR;
	}

	for (unsigned int i = 0; i < upperLimitHSV_.size(); ++i)
	{
		Mat inThisRangeImg;
		inRange(inputImageHSV_, lowerLimitHSV_.at(i), upperLimitHSV_.at(i), inThisRangeImg);
		
		if (inRangeImage_.empty())
		{
			inRangeImage_ = inThisRangeImg.clone();
		}
		else
		{
			Mat inPreviousRangeImg = inRangeImage_.clone();
			addWeighted(inPreviousRangeImg, 1.0, inThisRangeImg, 1.0, 0.0, inRangeImage_);
		}
	}

	return OK;
}


void ColorBlobDetector::addRange(const Scalar& lowerLimit, const Scalar& upperLimit) 
{ 
	lowerLimitHSV_.push_back(lowerLimit); 
	upperLimitHSV_.push_back(upperLimit); 
}
