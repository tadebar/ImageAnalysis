cmake_minimum_required(VERSION 2.8)

INCLUDE_DIRECTORIES(${IMAGE_ANALYSIS_INCLUDEPATHS})

add_executable(WebcamColorSegmentation
	main.cpp
	)

target_link_libraries(WebcamColorSegmentation 
   ${OpenCV_LIBS}
   Detector 
   )