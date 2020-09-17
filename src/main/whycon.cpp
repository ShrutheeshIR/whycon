#define _LARGEFILE_SOURCE
#define _FILE_OFFSET_BITS 64

#include "whycon.h"
//process command line arguments 

Whycon::Whycon(int no, float diam)
{
    numBots  = no;
    circleDiameter = diam;
	image = new CRawImage(imageWidth,imageHeight);
	trans = new CTransformation(imageWidth,imageHeight,circleDiameter,true);
	trans->transformType = TRANSFORM_NONE;		//in our case, 2D is the default
	for (int i = 0;i<MAX_PATTERNS;i++) detectorArray[i] = new CCircleDetect(imageWidth,imageHeight,i);
	image->getSaveNumber();

}

//void  Whycon::processimage(cv::Mat frame)
boost::python::list Whycon::processimage(boost::python::numpy::ndarray frame)
// void Whycon::processimage(boost::python::numpy::ndarray frame)
{
	image->data = (unsigned char*)frame.get_data();
	// image->data = frame.data;
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
    boost::python::dict marker_info;
    boost::python::list markers_info;

    for (int i = 0;i<numBots;i++){
        if (currentSegmentArray[i].valid)
        {
            marker_info["ID"] =  currentSegmentArray[i].ID;
            marker_info["x"] = -objectArray[i].y;
            marker_info["y"] = -objectArray[i].z;
            marker_info["z"] = objectArray[i].x;
            marker_info["pitch"] = objectArray[i].pitch;
            marker_info["roll"] = objectArray[i].roll;
            marker_info["yaw"] = objectArray[i].yaw;
            marker_info["err"] = -objectArray[i].error;
            markers_info.append(marker_info);
            // printf("Object %i %03f %03f %03f %03f %03f %03f %03f\n",currentSegmentArray[i].ID,-objectArray[i].y,-objectArray[i].z,objectArray[i].x,objectArray[i].pitch, objectArray[i].roll, objectArray[i].yaw, objectArray[i].error);
        }
    }
    return markers_info;
    
}

void Whycon::cleanmem()
{
    printf("CLEANING\n");
    for (int i = 0;i<MAX_PATTERNS;i++) delete this->detectorArray[i];
	delete this->trans;
	// delete this->image;

}




