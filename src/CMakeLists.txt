
cmake_minimum_required(VERSION 3.5)
PROJECT(whycon)

# FIND_PACKAGE( OpenCV REQUIRED )
find_package(PythonLibs 2 REQUIRED)
find_package(Boost COMPONENTS numpy python REQUIRED)

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
    # "main/runner.cpp"
    "boost_ext.cpp"
)

# ADD_EXECUTABLE(whycon ${whyconfiles})                           
# TARGET_LINK_LIBRARIES (whycon ${OpenCV_LIBS} pthread SDL SDL_ttf)

add_library(whycon2 MODULE ${whyconfiles} )

# Set up the libraries and header search paths for this target
target_link_libraries(whycon2 pthread SDL SDL_ttf ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
target_include_directories(whycon2 PRIVATE ${PYTHON_INCLUDE_DIRS} )

# add_library(whyc SHARED ${whyconfiles})