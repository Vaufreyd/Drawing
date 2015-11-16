/**
 * @file DrawTimestampData.h
 * @ingroup Drawing
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAW_TIMESTAMP_DATA__
#define __DRAW_TIMESTAMP_DATA__

#if defined WIN32 || defined WIN64
#define _WINSOCKAPI_   /* Prevent inclusion of winsock.h in windows.h */
#include <Windows.h>
#endif

#include "Drawable.h"
#include "../DataManagement/ReadTimestampRawFile.h"


namespace MobileRGBD {

/**
 * @class DrawTimestampRawData DrawTimestampRawData.cpp DrawTimestampRawData.h
 * @brief Mother class for all drawing complex class (*with* an associated raw file).
 *        Subclassing must be done by rewriting the Draw function.
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class DrawTimestampRawData : public Drawable, public ReadTimestampRawFile
{
public:
	/** @brief constructor. Draw the telemeter in the image. Default drawing mode is PointToLine.
	 * @param WorkingFile [in] Timestamp file to read.
	 * @param RawFile [in] Raw file to read if any (Default = "").
	 * @param SizeOfFrame [in] SizeOfFrame inside the raw file. (Default = 0 => can be set later);
	 */
	DrawTimestampRawData( const std::string &WorkingFile, const std::string& RawFile = "", int SizeOfFrame = 0 );

	/** @brief Virtual destructor, always.
	 */
	~DrawTimestampRawData() {}

	/** @brief Draw data in image. Will call the Process function.
	 * @param WhereToDraw [in] Drawing cv::Mat.
	 * @param pTimestamp [in] Timestamp of the data.
	 */
	virtual bool Draw( cv::Mat& WhereToDraw, const TimeB &pTimestamp );
};

} // namespace MobileRGBD

#endif // __DRAW_TIMESTAMP_DATA__