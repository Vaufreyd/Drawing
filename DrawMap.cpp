/**
 * @file DrawMap.cpp
 * @ingroup Drawing
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#include "DrawMap.h"

using namespace cv;
using namespace MobileRGBD;

/** @brief Static function to draw a GeometricMap object on a cv::Mat.
 *
 * @param x x of the drawing position (usually the robot position). This point is at the 2/3 of WhereToDraw.
 * @param y y of the drawing position (usually the robot position). This point is at the 1/2 of WhereToDraw.
 * @param o Orientation of the drawing position (usually the robot orientation).
 * @param Map The map to draw.
 * @param WhereToDraw The cv::Map where to draw the map.
 */
// static
void DrawMap::SimpleDraw( float x, float y, float o, GeometricMap& Map, cv::Mat& WhereToDraw )
{
	if ( Map.segments.size() != 0 )
	{
		// Draw map
		for( unsigned int i = 0; i < Map.segments.size(); i++ )
		{
			double tx = Map.segments[i].p0[0]-x;
			double ty = Map.segments[i].p0[1]-y;
			double newx = (cos(o)*tx+sin(o)*ty);
			double newy = (-sin(o)*tx+cos(o)*ty);

			// Draw segments, -0.2 is to correct map position in regards of position of lazer range finder on the robulab
			cv::Point P0( X_CoordonateToPixelCentered(-newy,WhereToDraw.cols), WhereToDraw.rows/3+WhereToDraw.rows-Y_CoordonateToPixelCentered(newx-0.2,WhereToDraw.rows) );

			tx = Map.segments[i].p1[0]-x;
			ty = Map.segments[i].p1[1]-y;
			newx = (cos(o)*tx+sin(o)*ty);
			newy = (-sin(o)*tx+cos(o)*ty);

			cv::Point P1( X_CoordonateToPixelCentered(-newy,WhereToDraw.cols), WhereToDraw.rows/3+WhereToDraw.rows-Y_CoordonateToPixelCentered(newx-0.2,WhereToDraw.rows) );
			cv::line( WhereToDraw, P0,  P1, CV_RGB(0,0,0), 2 );
		}
	}
}

/** @brief constructor. Draw localization from the robot.
 *
 * @param Folder [in] Main folder containing the data. Map file name will be search in 'Folder/Recording.map' and then loaded.
 */
DrawMap::DrawMap( const std::string& Folder ) : DrawTimestampData( Folder + LocalisationFileName )
{
	// Get the file name from the Map.name file
	std::string TmpS = Folder;
	TmpS += MapFileName;

	Map.loadMap( TmpS.c_str() );
}

/** @brief ProcessElement is a callback function called by mother classes when data are ready.
 *
 * @param RequestTimestamp [in] The timestamp of the data.
 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
 */
bool DrawMap::ProcessElement( const TimeB &RequestTimestamp, void * UserData )
{
	cv::Mat& WhereToDraw = *((cv::Mat*)UserData);

	if ( Map.segments.size() == 0 )
	{
		// Nothing to draw, thus we draw it!
		return true;
	}

	float x, y, o;
	if ( (sscanf(DataBuffer, "{\"x\":%f,\"y\":%f,\"o\":%f}", &x, &y, &o )) != 3 )
	{
		return false;
	}

	// Call the static function for drawing
	SimpleDraw( x, y, o, Map, WhereToDraw );

	return true;
}