#define _LARGEFILE_SOURCE
#define _FILE_OFFSET_BITS 64

#include "whycon.h"
//process command line arguments 

void processArgs(int argc,char* argv[]) 
{
	numBots = atoi(argv[1]);
	// circleDiameter = atof(argv[2]);
}


void initialize(int argc,char* argv[])
{
    processArgs(argc,argv);
	image = new CRawImage(imageWidth,imageHeight);
	trans = new CTransformation(imageWidth,imageHeight,circleDiameter,true);
	trans->transformType = TRANSFORM_NONE;		//in our case, 2D is the default
	for (int i = 0;i<MAX_PATTERNS;i++) detectorArray[i] = new CCircleDetect(imageWidth,imageHeight,i);
	image->getSaveNumber();
}


void processimage(cv::Mat frame)
{
	image->data = frame.data;
    for (int i = 0;i<numBots;i++){
        if (currentSegmentArray[i].valid){
            lastSegmentArray[i] = currentSegmentArray[i];
            currentSegmentArray[i] = detectorArray[i]->findSegment(image,lastSegmentArray[i]);
        }
    }

    //search for untracked (not detected in the last frame) robots 
    for (int i = 0;i<numBots;i++){
        if (currentSegmentArray[i].valid == false){
            lastSegmentArray[i].valid = false;
            currentSegmentArray[i] = detectorArray[i]->findSegment(image,lastSegmentArray[i]);
        }
        if (currentSegmentArray[i].valid == false) break;		//does not make sense to search for more patterns if the last one was not found
    }
    //perform transformations from camera to world coordinates
    for (int i = 0;i<numBots;i++){
        if (currentSegmentArray[i].valid){
            objectArray[i] = trans->transform(currentSegmentArray[i],false);
            numFound++;
            if (currentSegmentArray[i].x == lastSegmentArray[i].x) numStatic++;
        }
    }
    for (int i = 0;i<numBots;i++){
        if (currentSegmentArray[i].valid) printf("Object %i %03f %03f %03f %03f %03f %03f %03f\n",currentSegmentArray[i].ID,-objectArray[i].y,-objectArray[i].z,objectArray[i].x,objectArray[i].pitch, objectArray[i].roll, objectArray[i].yaw, objectArray[i].error);
    }
    
}

int main(int argc,char* argv[])
{
	//initialize logging system, camera and network connection 
    initialize(argc,argv);
	//setup timers to assess system performance
    /*
	cv::Mat frame = cv::imread("/home/olorin/Desktop/IISc/hand-pose/WhyCon/LCASWhycon/src/whycon/id/00000005.png");
	
	cv::Size size(640,480);//the dst image size,e.g.100x100
	cv::resize(frame,frame,size);
	int rows = frame.rows;
	int cols = frame.cols;
	printf("SIZE - %d, %d", rows, cols);
	printf("YASSSSSSSSSS\n\n\n\n\n");
    */

	cv::Mat frame;
	cv::VideoCapture cap(4);
	while (stop == false)
	{
		if (!cap.read(frame))
			stop = true;
		
		cv::imshow("IMAGE", frame);
		cv::waitKey(1);
		numFound = numStatic = 0;
        processimage(frame);
    }

	// printf()
	// numFound = numStatic = 0;

	// processimage(frame);
	// delete image;
	for (int i = 0;i<MAX_PATTERNS;i++) delete detectorArray[i];
	// camera->saveConfig("../etc/camera.cfg");
	// delete camera;
	delete trans;
	return 0;
}



