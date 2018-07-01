cmake_minimum_required(VERSION 2.8)

message(${IMAGE_ANALYSIS_INCLUDEPATHS})

include_directories(${IMAGE_ANALYSIS_INCLUDEPATHS})


set(DETECTOR_SRCS
	color_blob_detector.cpp
	color_blob_detector.h
	detector.h
)

add_library(Detector STATIC ${DETECTOR_SRCS})#
	
set_target_properties(Detector PROPERTIES LINKER_LANGUAGE CXX)
