/**
 * @file DrawInfraredView.h
 * @ingroup Drawing Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAW_INFRARED_VIEW_H__
#define __DRAW_INFRARED_VIEW_H__

#ifdef KINECT_1

	// No infrared stream from Kinect1

#endif // KINECT_1

#ifdef KINECT_2

#include "DrawRawData.h"

#define InfraredFileName "/infrared/infrared.timestamp"	/*!< @brief Timestamp file for the infrared input from Kinect1 or Kinect2 */
#define RawInfraredFileName "/infrared/infrared.raw"	/*!< @brief Raw file for the infrared input from Kinect1 or Kinect2  */

namespace MobileRGBD { namespace Kinect2 {

/**
 * @class DrawInfraredView DrawInfraredView.cpp DrawInfraredView.h
 * @brief Class to draw video stream from the Kinect2 data.
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class DrawInfraredView : public DrawRawData
{
public:
	/** @brief constructor. Draw data from the infrared stream of the Kinect2.
	 *
	 * @param Folder [in] Main folder containing the data. Body data will be search in 'Folder/infrared/' subfolder.
	 * @param SizeOfFrame [in] Size of each frame. Default value = InfraredWidth*InfraredHeight*InfraredBytesPerPixel.
	 */
	DrawInfraredView( const std::string& Folder, int SizeOfFrame = InfraredWidth*InfraredHeight*InfraredBytesPerPixel );

	/** @brief Virtual destructor, always.
	 */
	virtual ~DrawInfraredView();

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

#endif	// __DRAW_INFRARED_VIEW_H__
