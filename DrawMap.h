/**
 * @file DrawMap.h
 * @ingroup Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAW_MAP_H__
#define __DRAW_MAP_H__

#include <algorithm>
#include <GeometricMap.hpp>

#include "DrawTimestampData.h"
#include "Drawable.h"
#include "DrawingTools.h"

// To draw a map, we need to know about localisation
#include "DrawLocalization.h"

#define MapFileName "/Recording.map"	/*!< @brief File contaning the actual filename of the Map followed by the list of wall segments. */

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

	/** @brief Static function to draw a GeometricMap object on a cv::Mat.
	 *
	 * @param x x of the drawing position (usually the robot position). This point is at the 2/3 of WhereToDraw.
	 * @param y y of the drawing position (usually the robot position). This point is at the 1/2 of WhereToDraw.
	 * @param o Orientation of the drawing position (usually the robot orientation).
	 * @param Map The map to draw.
	 * @param WhereToDraw The cv::Map where to draw the map.
	 */
	static void SimpleDraw( float x, float y, float o, GeometricMap& Map, cv::Mat& WhereToDraw );

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
