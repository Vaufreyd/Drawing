/**
 * @file DrawTelemeter.cpp
 * @ingroup Drawing
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#include "DrawLaser.h"

#include "DrawingTools.h"
#include "Json/json_spirit.h"

#include <System/SimpleList.h>
#include <Messaging/Serializable.h>

using namespace cv;
using namespace MobileRGBD;

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

void DrawLaserData::Draw(float FirstAngle, float LastAngle, float Step, int NbEchos, Omiscid::SimpleList<float>& LaserMap, cv::Mat& WhereToDraw, int DrawingMode /*= PointToLine*/ )
{
#ifdef KINECT_2
	double CurrentAngle;
	int x,y;
	Point Origin(WhereToDraw.cols/2,2*WhereToDraw.rows/3);
			
// Draw Kinect Infrared, Depth, Body
	CurrentAngle = -70.6/2*Step;
	const double DepthViewMax = 4.5;
	x = X_CoordonateToPixelCentered(DepthViewMax*sin(CurrentAngle), WhereToDraw.cols);
	y = Y_CoordonateToPixelCentered(-DepthViewMax*cos(CurrentAngle), WhereToDraw.rows);
	Point P1(x,y);
			
	CurrentAngle =70.6/2*Step;
	x = X_CoordonateToPixelCentered(DepthViewMax*sin(CurrentAngle), WhereToDraw.cols);
	y = Y_CoordonateToPixelCentered(-DepthViewMax*cos(CurrentAngle), WhereToDraw.rows);
	Point P2(x,y);

// Draw Kinect RGB
	CurrentAngle = -87.5/2*Step;
	x = X_CoordonateToPixelCentered(10*sin(CurrentAngle), WhereToDraw.cols);
	y = Y_CoordonateToPixelCentered(-10*cos(CurrentAngle), WhereToDraw.rows);
	// cv::line( WhereToDraw, Origin, Point(x,y) ,CV_RGB(0,255,0), 2 );

	CurrentAngle =87.5/2*Step;
	x = X_CoordonateToPixelCentered(10*sin(CurrentAngle), WhereToDraw.cols);
	y = Y_CoordonateToPixelCentered(-10*cos(CurrentAngle), WhereToDraw.rows);
	// cv::line( WhereToDraw, Origin, Point(x,y) ,CV_RGB(0,255,0), 2 );
#else
// Draw Kinect
	double CurrentAngle = FirstAngle + 100*Step;
	int x = X_CoordonateToPixelCentered(10*sin(CurrentAngle), WhereToDraw.cols);
	int y = Y_CoordonateToPixelCentered(-10*cos(CurrentAngle), WhereToDraw.rows);
	cv::line( WhereToDraw, Point(WhereToDraw.cols/2,2*WhereToDraw.rows/3), Point(x,y) ,CV_RGB(0,255,0), 2 );

	CurrentAngle = FirstAngle + 167*Step;
	x = X_CoordonateToPixelCentered(10*sin(CurrentAngle), WhereToDraw.cols);
	y = Y_CoordonateToPixelCentered(-10*cos(CurrentAngle), WhereToDraw.rows);
	cv::line( WhereToDraw, Point(WhereToDraw.cols/2,2*WhereToDraw.rows/3), Point(x,y) ,CV_RGB(0,255,0), 2 );
#endif
	
	switch( DrawingMode )
	{
		case PointToLine:
			{
				CurrentAngle = FirstAngle;
				Point Precedent(WhereToDraw.cols/2,2*WhereToDraw.rows/3);
				for( LaserMap.First(); LaserMap.NotAtEnd(); LaserMap.Next() )
				{
					double value = LaserMap.GetCurrent();

					if ( value >= 10.0 )
					{
						// value = 10.0;
					}

					int x = X_CoordonateToPixelCentered(value*sin(CurrentAngle), WhereToDraw.cols );
					int y = Y_CoordonateToPixelCentered(-value*cos(CurrentAngle), WhereToDraw.rows);

					Point Courant(x,y);
					cv::line( WhereToDraw, Precedent, Courant, CV_RGB(255,0,0), 2 );

					Precedent = Courant;

					CurrentAngle += Step;
				}

				cv::line( WhereToDraw, Precedent, Point(WhereToDraw.cols/2,2*WhereToDraw.rows/3), CV_RGB(255,0,0), 2 );
				break;
			}

			case PointCloud:
			{
				CurrentAngle = FirstAngle;
				for( LaserMap.First(); LaserMap.NotAtEnd(); LaserMap.Next() )
				{
					double value = LaserMap.GetCurrent();

					if ( value >= 10.0 )
					{
						// value = 10.0;
					}

					int x = X_CoordonateToPixelCentered(value*sin(CurrentAngle), WhereToDraw.cols );
					int y = Y_CoordonateToPixelCentered(-value*cos(CurrentAngle), WhereToDraw.rows);

					Point Courant(x,y);
					cv::circle( WhereToDraw, Courant, 2, CV_RGB(255,0,0), -1 );

					CurrentAngle += Step;
				}

				break;
			}
	}
}

/** @brief ProcessElement is a callback function called by mother classes when data are ready.
 *
 * @param RequestTimestamp [in] The timestamp of the data.
 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
 */
bool DrawLaserData::ProcessElement( const TimeB &RequestTimestamp, void * UserData )
{
	cv::Mat& WhereToDraw = *((cv::Mat*)UserData);

	TelemeterInfo LaserData;
	LaserData.Unserialize(Omiscid::SimpleString(DataBuffer));

	Draw(LaserData.FirstAngle, LaserData.LastAngle, LaserData.Step, LaserData.NbEchos, LaserData.LaserMap, WhereToDraw, CurrentDrawingMode );

	return true;
}