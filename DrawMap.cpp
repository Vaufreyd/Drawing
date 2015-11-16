/**
 * @file DrawMap.cpp
 * @ingroup Drawing
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#include "DrawMap.h"

using namespace cv;
using namespace MobileRGBD;

/** @brief constructor. Draw localization from the robot.
 *
 * @param Folder [in] Main folder containing the data. Map file name will be search in 'Folder/Map.name' and then loaded.
 */
DrawMap::DrawMap( const std::string& Folder ) : DrawTimestampData( Folder + LocalisationFileName )
{
	// Get the file name from the Map.name file
	std::string TmpS = Folder;
	TmpS += MapFileName;
	FILE * fd = fopen( TmpS.c_str(), "rb" );
	if ( fd == nullptr )
	{
		fprintf( stderr, "Could not load '%s'\n", TmpS.c_str() );
		return;
	}

	// get map file name in LineBuffer (inherited from class ReadTimestamp)
	fscanf( fd, "%s", LineBuffer );
	fclose( fd );

	// Load map in current folder
	TmpS = Folder;
	TmpS += '/';
	TmpS += LineBuffer;
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

	float x, y, o;
	if ( (sscanf(DataBuffer, "{\"x\":%f,\"y\":%f,\"o\":%f}", &x, &y, &o )) != 3 )
	{
		return false;
	}

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
			Point P0( X_CoordonateToPixelCentered(-newy,WhereToDraw.cols), WhereToDraw.rows/3+WhereToDraw.rows-Y_CoordonateToPixelCentered(newx-0.2,WhereToDraw.rows) );

			tx = Map.segments[i].p1[0]-x;
			ty = Map.segments[i].p1[1]-y;
			newx = (cos(o)*tx+sin(o)*ty);
			newy = (-sin(o)*tx+cos(o)*ty);

			Point P1( X_CoordonateToPixelCentered(-newy,WhereToDraw.cols), WhereToDraw.rows/3+WhereToDraw.rows-Y_CoordonateToPixelCentered(newx-0.2,WhereToDraw.rows) );
			line( WhereToDraw, P0,  P1, CV_RGB(0,0,0), 2 );
		}
	}
	
	return true;
}