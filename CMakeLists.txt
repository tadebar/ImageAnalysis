cmake_minimum_required(VERSION 2.6)

project(ImageAnalysis)

set("OpenCV_DIR" "C:/OpenCV/Builds/install/")

find_package(OpenCV REQUIRED)

set(IMAGE_ANALYSIS_INCLUDEPATHS
  ${CMAKE_SOURCE_DIR}/src/include
  ${CMAKE_SOURCE_DIR}/src/lib/Detector  
  ${OpenCV_INCLUDE_DIRS}
  )

add_subdirectory(src)

