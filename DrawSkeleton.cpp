/**
 * @file DrawSkeleton.cpp
 * @ingroup Drawing Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#include "DrawSkeleton.h"

using namespace cv;

#ifdef KINECT_2

namespace MobileRGBD { namespace Kinect2 {

/** @brief ProcessElement is a callback function called by mother classes when data are ready.
 *
 * @param RequestTimestamp [in] The timestamp of the data.
 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
 */
bool DrawSkeleton::ProcessElement( const TimeB &RequestTimestamp, void * UserData )
{
	cv::Mat& WhereToDraw = *((cv::Mat*)UserData);

	if ( NumberOfSubFrames == 0 )
	{
		// Nothing to Draw, draw is done
		return true;
	}

	for( int i = 0; i < NumberOfSubFrames; i++ )
	{
		// Set memory to store Body
		CurrentBody.Set( ((unsigned char*)FrameBuffer)+i*FrameSize );

		// Draw it at the right palce
		CurrentBody.Draw(WhereToDraw, DrawInDepth);
	}

	return true;
}

}}	// namespace MobileRGBD::Kinect2

#endif