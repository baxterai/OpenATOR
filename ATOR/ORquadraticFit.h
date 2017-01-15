/*******************************************************************************
 *
 * File Name: ORquadraticFit.h (based on EdgiseFrame.java, version 1.17 (26-02-04) CSEM)
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3a7a 06-June-2012
 *
 *******************************************************************************/


#ifndef HEADER_OR_QUADRATIC_FIT
#define HEADER_OR_QUADRATIC_FIT


#include "ORglobalDefs.h"
#include "SHAREDvars.h"

	//For a quadratic fit there are 7 coefficients; a[0]..a[6]. but a[5] = a[6])
#define NUMBER_OF_COEFFICIENTS (6)


#define QUADRATIC_FIT_COLOUR_ZERO_CROSSING_R (255)
#define QUADRATIC_FIT_COLOUR_ZERO_CROSSING_G (0)
#define QUADRATIC_FIT_COLOUR_ZERO_CROSSING_B (0)
#define QUADRATIC_FIT_COLOUR_EDGE_R (0)
#define QUADRATIC_FIT_COLOUR_EDGE_G (192)
#define QUADRATIC_FIT_COLOUR_EDGE_B (0)
#define QUADRATIC_FIT_COLOUR_ZERO_CROSSING_ILLEGAL_R (255)
#define QUADRATIC_FIT_COLOUR_ZERO_CROSSING_ILLEGAL_G (0)
#define QUADRATIC_FIT_COLOUR_ZERO_CROSSING_ILLEGAL_B (255)


/*
#define FIX_NEW_HEITGER_CONSTRAST_THRESHOLD_ISSUE_MAYBE_DUE_TO_DEPTH_MAP_CHECK
#ifdef OR_USE_AMSTERDAM_TEST_IMAGE_DATA
	#define HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD (256*1.5)
	#define HEITGER_FEATURE_RGB_MAP_KERNEL_THRESHOLD (HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD/4.0)
	#define HEITGER_FEATURE_RGB_MAP_TOTAL_KERNEL_THRESHOLD (HEITGER_FEATURE_RGB_MAP_KERNEL_THRESHOLD*10.0)
#elif defined OR_USE_GOOGLE_MAPS
	#define HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD (100)	//50
	#define HEITGER_FEATURE_RGB_MAP_KERNEL_THRESHOLD (HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD/2.0)
	#define HEITGER_FEATURE_RGB_MAP_TOTAL_KERNEL_THRESHOLD (HEITGER_FEATURE_RGB_MAP_KERNEL_THRESHOLD*10.0)	//2.5
#elif defined OR_USE_STAR_MAPS
	#define HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD (256*1)
	#define HEITGER_FEATURE_RGB_MAP_KERNEL_THRESHOLD (HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD/4.0)
	#define HEITGER_FEATURE_RGB_MAP_TOTAL_KERNEL_THRESHOLD (HEITGER_FEATURE_RGB_MAP_KERNEL_THRESHOLD*10.0)
#else
	#ifdef FIX_NEW_HEITGER_CONSTRAST_THRESHOLD_ISSUE_MAYBE_DUE_TO_DEPTH_MAP_CHECK
		#define HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD (256)
		#define HEITGER_FEATURE_RGB_MAP_KERNEL_THRESHOLD (HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD/5.0)
		#define HEITGER_FEATURE_RGB_MAP_TOTAL_KERNEL_THRESHOLD (HEITGER_FEATURE_RGB_MAP_KERNEL_THRESHOLD*10.0)
	#else
		#define HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD (570)
		#define HEITGER_FEATURE_RGB_MAP_KERNEL_THRESHOLD (HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD/5.0)
		#define HEITGER_FEATURE_RGB_MAP_TOTAL_KERNEL_THRESHOLD (HEITGER_FEATURE_RGB_MAP_KERNEL_THRESHOLD*10.0)
	#endif

	//#define HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD (256*3/1.5)
	//#define HEITGER_FEATURE_RGB_MAP_TOTAL_KERNEL_THRESHOLD (HEITGER_FEATURE_RGB_MAP_CENTRE_THRESHOLD*3.5)
#endif
*/


#define EDGE_DETECT (true)
#define POINT_DETECT (false)


class QFZeroCrossing{

	private:
		/*There are currently no attributes of this class*/
	public:

		QFZeroCrossing(void); // constructor declaration
		~QFZeroCrossing();	//  and destructor.

		int x;
		int y;
		float zeroCrossingValueX;
		float zeroCrossingValueY;
		float alpha;
		float beta;
		float coefficient[NUMBER_OF_COEFFICIENTS];
		QFZeroCrossing * next;

		float dzalpha;
		float dzbeta;
		float dzTwoalpha;
		float dzTwobeta;
		float confidence;


		double depth;	//for 3DOD only
		#ifndef OR_METHOD_3DOD_USE_DYNAMIC_WORLD_COORD_DETERMINATION_USING_DEPTH
		int nearbyHitXValue;
		int nearbyHitYValue;
		#endif
		//#ifdef OR_METHOD3DOD_USE_QUADRATIC_FIT_EDGE_ZERO_CROSSING_MAP
		vec point;
		//#endif
};

double calculateAreaOfOneSideOfEdgeInAPixel(int xDevPointOnSide, int yDevPointOnSide, double zeroCrossingValueX, double zeroCrossingValueY, double alpha);


/*************************************** Edgise Frame High Level ('EdgiseFrameStandard') Methods ************************************/
	void generateZeroCrossingList(double * luminosityContrastMap, int imageWidth, int imageHeight, QFZeroCrossing * firstZeroCrossingInList, bool edgeDetect, double sensitivity, int dimension, double * pointMap, double * depthMap, int zoom, int interpixelMapType);
		void edgiseData(bool edgeDetect, bool createEnhancedImageDisplayingQuadraticFitInfo, QFZeroCrossing * currentZeroCrossingInList, int imageWidth, int imageHeight, double luminosityContrastMap[], double sensitivity, int dimension, double * pointMap, double * depthMap, int zoom, int interpixelMapType);
			bool calculateZeroCrossingAndOrientation(int x, int y, float coefficient[], bool edgeDetect, bool createEnhancedImageDisplayingQuadraticFitInfo, QFZeroCrossing * currentZeroCrossingInList);
/************************************ End Edgise Frame High Level ('EdgiseFrameStandard') Methods ***********************************/



/*********************************** Fit Methods *******************************/
void calculateQuadraticFitCoefficients(int x, int y, float coefficient[], double luminosityContrastMap[]);
void calculateQuadraticFitCoefficients3x3(int x, int y, float coefficient[], double luminosityContrastMap[]);
void calculateQuadraticFitCoefficients5x5(int x, int y, float coefficient[], double luminosityContrastMap[]);
/*********************************** End Fit Methods *******************************/

/********************************** Pixel Checking methods *******************************/
bool checkForTotalPositiveCurvature(float a3, float a4);
bool checkForTotalNegativeCurvature(float a3, float a4);
bool checkTotalNegativeCurvatureAbovePointThreshold(float a3, float a4);
/********************************** End Pixel Checking methods *******************************/

/********************************** Zero Crossing Checking methods ***********************************/
bool checkEdgeZeroCrossingObjectPassesThreshold(QFZeroCrossing * zc);
	bool checkEdgeZeroCrossingObjectContrastGradients(QFZeroCrossing * zc);
bool checkPointZeroCrossingObjectPassesThreshold(QFZeroCrossing * zc);
	//bool checkTotalNegativeCurvatureAbovePointThreshold(float a3, float a4);

/********************************** End Zero Crossing Checking methods ***********************************/

/********************************** Matrix Manipulation methods ***********************************/
float getSmallestEigenValue(float eigenValue[]);
void calculateEdgeZeroCrossing(float coefficient[], float beta, float zc[]);
void calculatePointZeroCrossing(float coefficient[], float zc[]);
void calculateEigenVector(float coefficient[], float ev, float eigenVector[]);
void calculateEigenValues(float coefficient[], float ev[]);
/********************************** End Matrix Manipulation methods ***********************************/

/*************************************** Get/Set Methods ************************************/
float getPixelFloat(int x, int y, double luminosityContrastMap[]);

/*************************************** End Get/Set Methods ********************************/






#endif
