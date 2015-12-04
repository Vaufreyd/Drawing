/**
 * @file DrawLaser.h
 * @ingroup Drawing
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAW_TELEMETER_H__
#define __DRAW_TELEMETER_H__

// #include "DrawingTools.h"
#include "DrawTimestampData.h"

#define TelemeterFileName "/robulab/Laser.timestamp"

namespace MobileRGBD {

/**
 * @class DrawLaserData DrawLaser.cpp DrawLaser.h
 * @brief Class to draw laser range finder around the robot.
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class DrawLaserData : public DrawTimestampData
{
public:
	/** @brief constructor. Draw the telemeter in the image. Default drawing mode is PointToLine.
	 */
	DrawLaserData() : DrawTimestampData("") {CurrentDrawingMode = PointToLine;}

	/** @brief constructor. Draw the telemeter in the image. Default drawing mode is PointToLine.
	 * @param Folder [in] Main folder containing the data. Body data will be search in 'Folder/robulab/' subfolder.
	 */
	DrawLaserData( const std::string& Folder )
		: DrawTimestampData( Folder + TelemeterFileName )
	{
		CurrentDrawingMode = PointToLine;
	}

	/** @brief Virtual destructor, always.
	 */
	virtual ~DrawLaserData() {}

	/** @brief ProcessElement is a callback function called by mother classes when data are ready.
	 *
	 * @param RequestTimestamp [in] The timestamp of the data.
	 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
	 */
	virtual bool ProcessElement( const TimeB &RequestedTimestamp, void * UserData = nullptr );

	/** @enum DrawTelemeterData::DrawingMode
	 *  @brief Enum flags to select read *or* write pipe, i.e. if we want to pipe from (read) or to (write) an external program
	 */
	enum { PointToLine = 0, PointCloud = 1 };
	int CurrentDrawingMode;
};

} // namespace MobileRGBD

#endif
