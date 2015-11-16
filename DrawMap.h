/**
 * @file DrawMap.h
 * @ingroup Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAW_MAP_H__
#define __DRAW_MAP_H__

#include <algorithm>
#include "../icp_localization/src/GeometricMap.hpp"

#include "DrawTimestampData.h"
#include "Drawable.h"
#include "DrawingTools.h"

// To draw a map, we need to know about localisation
#include "DrawLocalization.h"

#define MapFileName "/Map.name"	/*!< @brief File contaning the actual filename of the Map. Even if map differs, we will always find inforamtion about map file name here. */

namespace MobileRGBD {

/**
 * @class DrawMap DrawMap.cpp DrawMap.h
 * @brief Class to draw projected map arround the robot
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class DrawMap : public DrawTimestampData
{
public:
	/** @brief constructor. Draw localization from the robot.
	 *
	 * @param Folder [in] Main folder containing the data. Map file name will be search in 'Folder/Map.name' and then loaded.
	 */
	DrawMap( const std::string& Folder );

	/** @brief Virtual destructor, always.
	 */
	virtual ~DrawMap() {}


	/** @brief ProcessElement is a callback function called by mother classes when data are ready.
	 *
	 * @param RequestTimestamp [in] The timestamp of the data.
	 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
	 */
	virtual bool ProcessElement( const TimeB &RequestedTimestamp, void * UserData );

	GeometricMap Map;	/*!< @brief Object containing map segments */
};

} // namespace MobileRGBD

#endif // __DRAW_MAP_H__