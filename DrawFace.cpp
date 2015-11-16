/**
 * @file DrawFace.cpp
 * @ingroup Drawing Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#include "DrawFace.h"

using namespace cv;
using namespace MobileRGBD;


#ifdef KINECT_1

namespace MobileRGBD { namespace Kinect1 {

bool DrawFace::DrawElement( cv::Mat& WhereToDraw, const TimeB &RequestTimestamp )
{
	int x = 0, y = 0, size = 0;
	if ( sscanf( DataBuffer, "%*d %d, %d, %d", &x, &y, &size ) == 3 )
	{
		Point Courant(x/2,y/2);
		circle( WhereToDraw, Courant, size/2, cvScalar(0,255,0), 2 );
	}

	return true;
}

}}	// namespace MobileRGBD::Kinect1

#endif	// KINECT_1

#ifdef KINECT_2

namespace MobileRGBD { namespace Kinect2 {

/** @brief ProcessElement is a callback function called by mother classes when data are ready.
 *
 * @param RequestTimestamp [in] The timestamp of the data.
 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
 */
bool DrawFace::ProcessElement( const TimeB &RequestTimestamp, void *UserData )
{
	cv::Mat& WhereToDraw = *((cv::Mat*)UserData);

	if ( NumberOfSubFrames == 0 )
	{
		// Nothing to Draw, draw is done
		return true;
	}

	for( int i = 0; i < NumberOfSubFrames; i++ )
	{
		// Initialise memory block for a face
		CurrentFace.Set( ((unsigned char*)FrameBuffer) + i*FrameSize );

		// Draw it
		CurrentFace.Draw(WhereToDraw, DrawInDepth);
	}

	return true;
}

}}	// namespace MobileRGBD::Kinect1

#endif // KINECT_2