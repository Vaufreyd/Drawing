/**
 * @file DrawDepthView.h
 * @ingroup Drawing Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAW_DEPTH_VIEW_H__
#define __DRAW_DEPTH_VIEW_H__

#include "DrawRawData.h"

#define DepthFileName "/depth/depth.timestamp"	/*!< @brief Timestamp file for the depth input from Kinect1 or Kinect2 */
#define RawDepthFileName "/depth/depth.raw"		/*!< @brief Raw file for the depth input from Kinect1 or Kinect2  */

#ifdef KINECT_1

namespace MobileRGBD { namespace Kinect1 {

}} // namesapce MobileRGBD::Kinect1

#endif // KINECT_1

#ifdef KINECT_2

namespace MobileRGBD { namespace Kinect2 {

/**
 * @class DrawDepthView DrawDepthView.cpp DrawDepthView.h
 * @brief Class to draw depth stream from the Kinect2 data.
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class DrawDepthView : public DrawRawData
{
public:
	/** @brief constructor. Draw data from the depth stream of the Kinect2.
	 *
	 * @param Folder [in] Main folder containing the data. Body data will be search in 'Folder/depth/' subfolder.
	 * @param SizeOfFrame [in] Size of each frame. Default value = DepthWidth*DepthHeight*DepthBytesPerPixel.
	 */
	DrawDepthView( const std::string& Folder, int SizeOfFrame = DepthWidth*DepthHeight*DepthBytesPerPixel )
		: DrawRawData( Folder + DepthFileName, Folder + RawDepthFileName, SizeOfFrame )
	{
		ImageBuffer = new unsigned char[DepthWidth*DepthHeight*3]; // BGR data
	}

	/** @brief Static function to draw data from RGB raw Kinect buffer.
	 *
	 */
	static void Draw( cv::Mat& WhereToDraw, void * FrameBuffer, void * DrawingBuffer = nullptr );

	/** @brief Virtual destructor, always.
	 */
	~DrawDepthView()
	{
		if ( ImageBuffer != nullptr )
		{
			delete ImageBuffer;
		}
	};

	/** @brief ProcessElement is a callback function called by mother classes when data are ready.
	 *
	 * @param RequestTimestamp [in] The timestamp of the data.
	 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
	 */
	virtual bool ProcessElement( const TimeB &RequestTimestamp, void * UserData = nullptr );

protected:
	unsigned char * ImageBuffer;		/*!< @brief Buffer to work on the data. */
};

}} // namespace MobileRGBD::Kinect2

#endif // KINECT_2

#endif	// __DRAW_DEPTH_VIEW_H__
