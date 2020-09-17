
cmake_minimum_required(VERSION 3.5)
PROJECT(whycon)

FIND_PACKAGE( OpenCV REQUIRED )

INCLUDE_DIRECTORIES(main common imageproc)
set(CMAKE_SHARED_MODULE_PREFIX "")

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

# add_library(whycon2 MODULE ${whyconfiles} )

