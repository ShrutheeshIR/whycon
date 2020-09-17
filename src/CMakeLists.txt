
cmake_minimum_required(VERSION 2.8)
PROJECT(whycon)

FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} common imageproc)

file(GLOB whyconfiles
    "common/*.h"
    "common/*.cpp"
    "common/*.c"
    "imageproc/*.h"
    "imageproc/*.cpp"
    "imageproc/*.c"
    "main/whycon.cpp"
    "main/runner.cpp"
)

ADD_EXECUTABLE(whycon ${whyconfiles})                           
TARGET_LINK_LIBRARIES (whycon ${OpenCV_LIBS} pthread SDL SDL_ttf)

add_library(whyc SHARED main/whycon.cpp)