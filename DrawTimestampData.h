/**
 * @file DrawTimestampRawData.h
 * @ingroup Drawing
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAW_TIMESTAMP_RAW_DATA__
#define __DRAW_TIMESTAMP_RAW_DATA__

#include "opencv2/video/tracking.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "Drawable.h"
#include "../DataManagement/ReadTimestampRawFile.h"

#if defined WIN32 || defined WIN64
#define _WINSOCKAPI_   /* Prevent inclusion of winsock.h in windows.h */
#include <Windows.h>
#endif

namespace MobileRGBD {

/**
 * @class DrawTimestampData DrawTimestampData.cpp DrawTimestampData.h
 * @brief Mother class for all drawing simple classes (*without* an associated raw file).
 *        Subclassing must be done by rewriting the Draw function.
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class DrawTimestampData : public Drawable, public ReadTimestampFile
{
public:
	/** @brief constructor. Draw the telemeter in the image. Default drawing mode is PointToLine.
	 * @param WorkingFile [in] Timestamp file to read.
	 */
	DrawTimestampData( const std::string &WorkingFile );

	/** @brief Virtual destructor, always.
	 */
	virtual ~DrawTimestampData() {}

	/** @brief Draw data in image. Will call the Process function.
	 * @param WhereToDraw [in] Drawing cv::Mat.
	 * @param pTimestamp [in] Timestamp of the data.
	 */
	virtual bool Draw( cv::Mat& WhereToDraw, const TimeB &pTimestamp );
};

} // namespace MobileRGBD

#endif // __DRAW_TIMESTAMP_RAW_DATA__