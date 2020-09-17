#include "whycon.h"

int main(int argc,char* argv[])
{
    whycon *why = new whycon();
	//initialize logging system, camera and network connection 
    why->initialize(argc,argv);
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
    bool stop = false;
	cv::VideoCapture cap(4);
	while (stop == false)
	{
		if (!cap.read(frame))
			stop = true;
		
		cv::imshow("IMAGE", frame);
		cv::waitKey(1);
		why->numFound = why->numStatic = 0;
        why->processimage(frame);
    }

	// printf()
	// numFound = numStatic = 0;

	// processimage(frame);
	// delete image;
	for (int i = 0;i<MAX_PATTERNS;i++) delete why->detectorArray[i];
	// camera->saveConfig("../etc/camera.cfg");
	// delete camera;
	delete why->trans;
	return 0;
}
