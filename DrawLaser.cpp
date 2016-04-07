/**
 * @file DrawLaser.cpp
 * @ingroup Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#include "DrawLaser.h"

#include "DrawingTools.h"
#include "Json/json_spirit.h"

using namespace cv;
using namespace MobileRGBD;


/** @brief ProcessElement is a callback function called by mother classes when data are ready.
 *
 * @param RequestTimestamp [in] The timestamp of the data.
 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
 */
bool DrawLaserData::ProcessElement( const TimeB &RequestTimestamp, void * UserData )
{
	cv::Mat& WhereToDraw = *((cv::Mat*)UserData);

	LaserData.Unserialize(Omiscid::SimpleString(DataBuffer));

// Show Kinect field of view
#ifdef KINECT_2
	double CurrentAngle;
	int x,y;
	Point Origin(WhereToDraw.cols/2,2*WhereToDraw.rows/3);
			
// Draw Kinect Infrared, Depth, Body
	CurrentAngle = -70.6/2*LaserData.Step;
	const double DepthViewMax = 4.5;
	x = X_CoordonateToPixelCentered(DepthViewMax*sin(CurrentAngle), WhereToDraw.cols);
	y = Y_CoordonateToPixelCentered(-DepthViewMax*cos(CurrentAngle), WhereToDraw.rows);
	Point P1(x,y);
			
	CurrentAngle =70.6/2*LaserData.Step;
	x = X_CoordonateToPixelCentered(DepthViewMax*sin(CurrentAngle), WhereToDraw.cols);
	y = Y_CoordonateToPixelCentered(-DepthViewMax*cos(CurrentAngle), WhereToDraw.rows);
	Point P2(x,y);

// Draw Kinect RGB
	CurrentAngle = -87.5/2*LaserData.Step;
	x = X_CoordonateToPixelCentered(10*sin(CurrentAngle), WhereToDraw.cols);
	y = Y_CoordonateToPixelCentered(-10*cos(CurrentAngle), WhereToDraw.rows);
	// cv::line( WhereToDraw, Origin, Point(x,y) ,CV_RGB(0,255,0), 2 );

	CurrentAngle =87.5/2*LaserData.Step;
	x = X_CoordonateToPixelCentered(10*sin(CurrentAngle), WhereToDraw.cols);
	y = Y_CoordonateToPixelCentered(-10*cos(CurrentAngle), WhereToDraw.rows);
	// cv::line( WhereToDraw, Origin, Point(x,y) ,CV_RGB(0,255,0), 2 );
#else
// Draw Kinect
	double CurrentAngle = FirstAngle + 100*LaserData.Step;
	int x = X_CoordonateToPixelCentered(10*sin(CurrentAngle), WhereToDraw.cols);
	int y = Y_CoordonateToPixelCentered(-10*cos(CurrentAngle), WhereToDraw.rows);
	cv::line( WhereToDraw, Point(WhereToDraw.cols/2,2*WhereToDraw.rows/3), Point(x,y) ,CV_RGB(0,255,0), 2 );

	CurrentAngle = FirstAngle + 167*LaserData.Step;
	x = X_CoordonateToPixelCentered(10*sin(CurrentAngle), WhereToDraw.cols);
	y = Y_CoordonateToPixelCentered(-10*cos(CurrentAngle), WhereToDraw.rows);
	cv::line( WhereToDraw, Point(WhereToDraw.cols/2,2*WhereToDraw.rows/3), Point(x,y) ,CV_RGB(0,255,0), 2 );
#endif
	
	switch( CurrentDrawingMode )
	{
		// Draw telemeter as connected lines
		case PointToLine:
			{
				CurrentAngle = LaserData.FirstAngle;
				Point Precedent(WhereToDraw.cols/2,2*WhereToDraw.rows/3);
				for( LaserData.LaserMap.First(); LaserData.LaserMap.NotAtEnd(); LaserData.LaserMap.Next() )
				{
					double value = LaserData.LaserMap.GetCurrent();

					if ( value >= 10.0 )
					{
						// value = 10.0;
					}

					int x = X_CoordonateToPixelCentered(value*sin(CurrentAngle), WhereToDraw.cols );
					int y = Y_CoordonateToPixelCentered(-value*cos(CurrentAngle), WhereToDraw.rows);

					Point Courant(x,y);
					cv::line( WhereToDraw, Precedent, Courant, CV_RGB(255,0,0), 2 );

					Precedent = Courant;

					CurrentAngle += LaserData.Step;
				}

				cv::line( WhereToDraw, Precedent, Point(WhereToDraw.cols/2,2*WhereToDraw.rows/3), CV_RGB(255,0,0), 2 );
				break;
			}

		// Draw telemeter as point cloud
		case PointCloud:
			{
				CurrentAngle = LaserData.FirstAngle;
				for( LaserData.LaserMap.First(); LaserData.LaserMap.NotAtEnd(); LaserData.LaserMap.Next() )
				{
					double value = LaserData.LaserMap.GetCurrent();

					if ( value >= 10.0 )
					{
						// value = 10.0;
					}

					int x = X_CoordonateToPixelCentered(value*sin(CurrentAngle), WhereToDraw.cols );
					int y = Y_CoordonateToPixelCentered(-value*cos(CurrentAngle), WhereToDraw.rows);

					Point Courant(x,y);
					cv::circle( WhereToDraw, Courant, 2, CV_RGB(255,0,0), -1 );

					CurrentAngle += LaserData.Step;
				}

				break;
			}
	}

	return true;
}