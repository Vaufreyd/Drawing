/**
 * @file DrawRawData.h
 * @ingroup Drawing
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAW_RAW_DATA_H__
#define __DRAW_RAW_DATA_H__

#ifdef KINECT_2
	#include "../Kinect/KinectBasics.h"
#endif

#include "DrawTimestampRawData.h"
#include "Drawable.h"

namespace MobileRGBD {

/**
 * @class DrawRawData DrawRawData.cpp DrawRawData.h
 * @brief DrawRawData is a intermediate class only to instanciate DrawTimestampRawData properly.
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class DrawRawData : public DrawTimestampRawData
{
public:
	/** @brief constructor. Draw localization from the robot.
	 *
	 * @param WorkingFile [in] Timestamp file name.
	 * @param RawFile [in] Associated raw file name.
	 * @param SizeOfFrame [in] Size of each frame in raw file.
	 */
	DrawRawData( const std::string& WorkingFile, const std::string& RawFile, int SizeOfFrame )
		: DrawTimestampRawData( WorkingFile, RawFile, SizeOfFrame )
	{
	}

	/** @brief Virtual destructor, always.
	 */
	virtual ~DrawRawData() {}
};

} // namespace MobileRGBD


#endif // __DRAW_RAW_DATA_H__