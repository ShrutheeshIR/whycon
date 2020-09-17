#define _LARGEFILE_SOURCE
#define _FILE_OFFSET_BITS 64

#include "whycon.h"
//process command line arguments 

void whycon::processArgs(int argc,char* argv[]) 
{
	numBots = atoi(argv[1]);
	circleDiameter = atof(argv[2]);
}


extern "C" void whycon::initialize(int argc,char* argv[])
{
    processArgs(argc,argv);
	image = new CRawImage(imageWidth,imageHeight);
	trans = new CTransformation(imageWidth,imageHeight,circleDiameter,true);
	trans->transformType = TRANSFORM_NONE;		//in our case, 2D is the default
	for (int i = 0;i<MAX_PATTERNS;i++) detectorArray[i] = new CCircleDetect(imageWidth,imageHeight,i);
	image->getSaveNumber();
}


extern "C" void whycon::processimage(uchar * u_frame)
{
	image->data = u_frame;
    for (int i = 0;i<whycon::numBots;i++){
        if (whycon::currentSegmentArray[i].valid){
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




