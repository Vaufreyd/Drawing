/**
 * @file DrawSkeleton.h
 * @ingroup Drawing Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAW_SKELETON_H__
#define __DRAW_SKELETON_H__

#define SkeletonFileName "/skeleton/skeleton.timestamp"

#ifdef KINECT_1
	// to refactor
#endif

#ifdef KINECT_2

#include "DrawRawData.h"
#include "Kinect/KinectBody.h"

#define RawSkeletonFileName "/skeleton/skeleton.raw"

namespace MobileRGBD { namespace Kinect2 {

	/**
 * @class DrawSkeleton DrawSkeleton.cpp DrawSkeleton.h
 * @brief Class to draw skeletons (aka Bodies) from the Kinect2 data.
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class DrawSkeleton : public DrawRawData
{
public:
	/** @brief constructor. Draw data from the skeleton stream of the Kinect2.
	 *
	 * @param Folder [in] Main folder containing the data. Body data will be search in 'Folder/skeleton/' subfolder.
	 * @param _DrawInDepth [in] Boolean to know if we want to draw in Depth of in Video stream (for scaling purpose)
	 */
	DrawSkeleton( const std::string& Folder, bool _DrawInDepth = true )
		: DrawRawData( Folder + SkeletonFileName, Folder + RawSkeletonFileName, 0 /* will be corrected late in constructor */ )
	{
		// Skeleton's are not in single mode
		Mode = SubFramesMode;

		DrawInDepth = _DrawInDepth;

		// Correct size of frame
		CurrentBody.Set((unsigned char*)nullptr);
		FrameSize = CurrentBody.BodySize;
	}

	/** @brief Virtual destructor, always.
	 */
	virtual ~DrawSkeleton() {};

	bool DrawInDepth;	/*!< @brief Boolean value to store if we draw in Depth or in Video (for scaling purpose) */

protected:
	/** @brief ProcessElement is a callback function called by mother classes when data are ready.
	 *
	 * @param RequestTimestamp [in] The timestamp of the data.
	 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
	 */
	virtual bool ProcessElement( const TimeB &RequestTimestamp, void * UserData = nullptr );

	KinectBody CurrentBody;		/*!< @brief KinectBody object to store data to draw */
};

}}	// namespace MobileRGBD::Kinect2

#endif // KINECT_2

#endif