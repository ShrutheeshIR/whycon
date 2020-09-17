#include <stdlib.h>
// #include "CCamera.h"
#include "CTimer.h"
#include "CCircleDetect.h"
#include "CPosition.h"
#include "CTransformation.h"
#include <SDL/SDL.h>
#include "CPositionServer.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


//-----These parameters need to be adjusted by the user -----------------------

//Adjust camera resolution here
// int  imageWidth= 1600;
// int  imageHeight = 1200;

class whycon{
    public:

        int  imageWidth= 640;
        int  imageHeight = 480;

        //Adjust the black circle diameter [m] 
        float circleDiameter = 0.038;

        /*Adjust the X and Y dimensions of the coordinate system*/ 
        float fieldLength = 1.00;
        float fieldWidth = 1.00;
        //----------------------------------------------------------------------------

        //Max GUI dimensions 

        /*robot detection variables*/
        int numBots = 0;				//num of robots to track
        int numFound = 0;				//num of robots detected in the last step
        int numStatic = 0;				//num of non-moving robots  
        CCircleDetect *detectorArray[MAX_PATTERNS];	//detector array (each pattern has its own detector)
        SSegment currentSegmentArray[MAX_PATTERNS];	//segment array (detected objects in image space)
        SSegment lastSegmentArray[MAX_PATTERNS];	//segment position in the last step (allows for tracking)
        STrackedObject objectArray[MAX_PATTERNS];	//object array (detected objects in metric space)
        CTransformation *trans;				//allows to transform from image to metric coordinates

        /*variables related to (auto) calibration*/
        const int calibrationSteps = 20;		//how many measurements to average to estimate calibration pattern position (manual calib)
        const int autoCalibrationSteps = 30; 		//how many measurements to average to estimate calibration pattern position (automatic calib)  
        const int autoCalibrationPreSteps = 10;		//how many measurements to discard before starting to actually auto-calibrating (automatic calib)  
        int calibNum = 5;				//number of objects acquired for calibration (5 means calibration winished inactive)
        STrackedObject calib[5];			//array to store calibration patterns positions
        STrackedObject calibTmp[20];	//array to store several measurements of a given calibration pattern
        int calibStep = calibrationSteps+2;		//actual calibration step (num of measurements of the actual pattern)
        bool autocalibrate = false;			//is the autocalibration in progress ?
        ETransformType lastTransformType = TRANSFORM_3D;//pre-calibration transform (used to preserve pre-calibation transform type)
        int wasBots = 1;				//pre-calibration number of robots to track (used to preserve pre-calibation number of robots to track)

        /*program flow control*/
        bool saveVideo = true;				//save video to output folder?
        bool saveLog = true;				//save log to output folder?
        int moveVal = 1;				//how many frames to process ?
        int moveOne = moveVal;				//how many frames to process now (setting moveOne to 0 or lower freezes the video stream) 

        /*communication input (camera) and output (socket server)*/
        // CCamera* camera;
        CRawImage *image;

        void processArgs(int argc,char* argv[]);
        void initialize(int argc,char* argv[]);
        void processimage(cv::Mat frame);


};