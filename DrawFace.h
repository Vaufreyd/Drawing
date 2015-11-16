/**
 * @file DrawFace.h
 * @ingroup Drawing Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAW_FACE_H__
#define __DRAW_FACE_H__

#include "DrawRawData.h"
#define FaceFileName "/face/faces.timestamp"

#ifdef KINECT_1

#include "DrawTimestampData.h"

namespace MobileRGBD { namespace Kinect1 {

/**
 * @class DrawFace DrawFace.cpp DrawFace.h
 * @brief Class to draw face from the Kinect1 data.
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class DrawFace : public DrawTimestampData
{
public:
	DrawFace( const std::string& Folder, const std::string& FileIn = FaceFileName, int SizeOfFrame = 640*480*4 )
		: DrawTimestampData( Folder + FileIn )
	{
	}

	~DrawFace() {};

	virtual bool DrawElement( cv::Mat& WhereToDraw, const TimeB &RequestTimestamp );
};

}} // namespace MobileRGBD::Kinect1

#endif // KINECT_1


#ifdef KINECT_2

#include "Kinect/KinectFace.h"

#define RawFaceFileName "/face/face.raw"

namespace MobileRGBD { namespace Kinect2 {

/**
 * @class DrawFace DrawFace.cpp DrawFace.h
 * @brief Class to draw face from the Kinect1 data.
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class DrawFace : public DrawRawData
{
public:
	/** @brief constructor. Draw data from the face stream of the Kinect2.
	 *
	 * @param Folder [in] Main folder containing the data. Body data will be search in 'Folder/video/' subfolder.
	 * @param width [in] Width of the frame (for scaling purpose).
	 * @param height [in] Height of the frame (for scaling purpose).
	 * @param _DrawInDepth [in] Do we draw in a Depth frame or a video Frame. Default = true;
	 */
	DrawFace( const std::string& Folder, int width, int height, bool _DrawInDepth = true )
		: DrawRawData( Folder + FaceFileName, Folder + RawFaceFileName, 0 /* actual face will be corrected late in constructor */ )
	{
		// Skeleton's are not in single mode
		Mode = SubFramesMode;

		ImgWidth = width;
		ImghHeight = height;

		DrawInDepth = _DrawInDepth;

		// Correct size of frame
		CurrentFace.Set((unsigned char*)nullptr);
		FrameSize = CurrentFace.FaceSize;
	}

	virtual ~DrawFace() {};

protected:
	/** @brief ProcessElement is a callback function called by mother classes when data are ready.
	 *
	 * @param RequestTimestamp [in] The timestamp of the data.
	 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
	 */
	virtual bool ProcessElement( const TimeB &RequestTimestamp, void * UserData = nullptr );

	bool DrawInDepth;	/*!< @brief Memory of the drawing style (in Depth or not) */

	// Img Params for scaling purpose
	int ImgWidth;		/*!< @brief Memory of the width for scaling purpose */
	int ImghHeight;		/*!< @brief Memory of the height for scaling purpose */

	MobileRGBD::Kinect2::KinectFace CurrentFace;		/*!< @brief Current face */
};

}} // namespace MobileRGBD::Kinect2

#endif // KINECT_2

#endif	// __DRAW_FACE_H__