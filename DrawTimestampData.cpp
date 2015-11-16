/**
 * @file DrawTimestampData.cpp
 * @ingroup Drawing
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#include "DrawTimestampData.h"

using namespace cv;
using namespace MobileRGBD;

/** @brief constructor. Draw the telemeter in the image. Default drawing mode is PointToLine.
 * @param WorkingFile [in] Timestamp file to read.
 * @param RawFile [in] Raw file to read if any (Default = "").
 * @param SizeOfFrame [in] SizeOfFrame inside the raw file. (Default = 0 => can be set later);
 */
DrawTimestampData::DrawTimestampData( const std::string &WorkingFile )
	: ReadTimestampFile( WorkingFile )
{
}


/** @brief Draw data in image. Will call the Process function.
 * @param WhereToDraw [in] Drawing cv::Mat.
 * @param pTimestamp [in] Timestamp of the data.
 */
bool DrawTimestampData::Draw( Mat& WhereToDraw, const TimeB &RequestTimestamp )
{
	return Process( RequestTimestamp, (void*)&WhereToDraw );
}
