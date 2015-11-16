/**
 * @file DrawBodyIndexView.h
 * @ingroup Drawing Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAW_BODY_INDEX__VIEW_H__
#define __DRAW_BODY_INDEX__VIEW_H__

#ifdef KINECT_2

#include "DrawRawData.h"

namespace MobileRGBD { namespace Kinect2 {

#define BodyIndexFileName "/body_index/body_index.timestamp"	/*!< @brief Timestamp file for the body_index from Kinect2 */
#define RawBodyIndexFileName "/body_index/body_index.raw"		/*!< @brief Raw file for the body_index from Kinect2 */

/**
 * @class DrawBodyIndexView DrawBodyIndexView.cpp DrawBodyIndexView.h
 * @brief Class to draw BodyIndex from the Kinect data.
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class DrawBodyIndexView : public DrawRawData
{
public:
	static unsigned char Colors[6][3];		/*!< @brief shared BRG color index for body drawing. First body will always have the sale color, etc. */

	/** @brief constructor. Draw data from the Body stream of the Kinect2.
	 *
	 * @param Folder [in] Main folder containing the data. Body data will be search in 'Folder/body_index/' subfolder.
	 * @param SizeOfFrame [in] Size of each frame. Default value = DepthWidth*DepthHeight (1 byte per pixel).
	 */
	DrawBodyIndexView( const std::string& Folder, int SizeOfFrame = DepthWidth*DepthHeight );	// 1 byte per pixel

	/** @brief Virtual destructor, always.
	 */
	virtual ~DrawBodyIndexView();

	/** @brief ProcessElement is a callback function called by mother classes when data are ready.
	 *
	 * @param RequestTimestamp [in] The timestamp of the data.
	 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
	 */
	virtual bool ProcessElement( const TimeB &RequestTimestamp, void * UserData = nullptr );

protected:
	unsigned char * ImageBuffer;		/*!< @brief Buffer to work on the data. */
};

}} // namespace MobileRGBD::Kinect2

#endif

#endif	// __DRAW_BODY_INDEX__VIEW_H__
