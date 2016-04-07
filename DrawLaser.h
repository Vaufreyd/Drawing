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

 #include <Messaging/Serializable.h>

namespace MobileRGBD {


/**
 * @class TelemeterInfo DrawLaserData.cpp
 * @brief Unserialize JSON Data from laser timestamp file
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class TelemeterInfo : public Omiscid::Serializable
{
public:
	float FirstAngle;						/*!< First angle of the laser range finder */
	float LastAngle;						/*!< Last angle of the laser range finder */
	float Step;								/*!< Step between angles of the laser range finder */
	int NbEchos;							/*!< Number of laser echos */
	Omiscid::SimpleList<float> LaserMap;	/*!< NbEchos float values ordered from First angle to last angle */

	/* @brief DeclareSerializeMapping declare association between Values and key string in JSON. Will be used
		both for serialization and unserialiazation.
	 */
	virtual void DeclareSerializeMapping()
	{
		AddToSerialization( "FirstAngle", FirstAngle );
		AddToSerialization( "LastAngle", LastAngle );
		AddToSerialization( "Step", Step );
		AddToSerialization( "NbEchos", NbEchos );
		AddToSerialization( "LaserMap", LaserMap );
	}
};

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

	TelemeterInfo LaserData;
};

} // namespace MobileRGBD

#endif
