cmake_minimum_required(VERSION 2.6)

project(ImageAnalysis)

set("OpenCV_DIR" "C:/OpenCV/Builds/install/")

find_package(OpenCV REQUIRED)

add_executable(WebcamColorSegmentation WebcamColorSegmentation.cpp)

target_link_libraries(ImageAnalysis ${OpenCV_LIBS} )