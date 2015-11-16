/**
 * @file Drawable.h
 * @ingroup Drawing Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include "opencv2/video/tracking.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "../DataManagement/TimestampTools.h"

#if defined WIN32 || defined WIN64
#define _WINSOCKAPI_   /* Prevent inclusion of winsock.h in windows.h */
#include <Windows.h>
#endif

namespace MobileRGBD {

/**
 * @class Drawable Drawable.cpp Drawable.h
 * @brief Abstract class for all drawing objects. Subclasses must define the the Draw function.
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class Drawable
{
public:
	/** @brief constructor. Empty.
	 */
	Drawable() {}

	/** @brief virtual destructor. Empty.
	 */
	virtual ~Drawable() {}

	/** @brief Draw a data in a cv::Mat object. Data are scaled to fit the cv::Mat.
	 *
	 * @param RequesteWhereToDrawdTimestamp [in,out] Place to.
	 * @param pTimestamp [in] Timestamp of the data.
	 * @return true if data can be read and drawn.
	 */
	virtual bool Draw( cv::Mat& WhereToDraw, const TimeB &pTimestamp ) = 0;
};

} // namespace MobileRGBD

#endif