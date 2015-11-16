/**
 * @file DrawLocalization.cpp
 * @ingroup Drawing
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#include "DrawLocalization.h"

using namespace cv;
using namespace MobileRGBD;

/** @brief ProcessElement is a callback function called by mother classes when data are ready.
	*
	* @param RequestTimestamp [in] The timestamp of the data.
	* @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
	*/
bool DrawLocalization::ProcessElement( const TimeB &RequestTimestamp, void * UserData )
{
	cv::Mat& WhereToDraw = *((cv::Mat*)UserData);

	float x, y, o;
	if ( (sscanf(DataBuffer, "{\"x\":%f,\"y\":%f,\"o\":%f}", &x, &y, &o )) != 3 )
	{
		return false;
	}

	char tmpc[512];
	sprintf( tmpc, "X=%.3f Y=%.3f O=%.3f", x, y, o );

	int baseline = 0;
	Size TSize;

	baseline = 0;
	TSize = getTextSize(tmpc, FONT_HERSHEY_COMPLEX, 0.5, 1, &baseline);

	putText( WhereToDraw, tmpc, Point((WhereToDraw.cols)/2-TSize.width/2,TSize.height+5), FONT_HERSHEY_COMPLEX, 0.5, Scalar(0, 0, 0), 1, 8 );

	// We render flip images, thus flip it, it will be flap back after global flip on the whole image
	// cv::Mat ToFlip( WhereToDraw, Rect((WhereToDraw.cols)/2-TSize.width/2,0,TSize.width,TSize.height+5) );
	flip( WhereToDraw, WhereToDraw, 1 );

	return true;
}