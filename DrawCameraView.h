/**
 * @file DrawCameraView.h
 * @ingroup Drawing Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAW_CAMERA_VIEW_H__
#define __DRAW_CAMERA_VIEW_H__

#include "DrawRawData.h"

#define VideoFileName "/video/video.timestamp"	/*!< @brief Timestamp file for the video input from Kinect1 or Kinect2 */
#define RawVideoFileName "/video/video.raw"		/*!< @brief Raw file for the video input from Kinect1 or Kinect2  */

#ifdef KINECT_1

namespace MobileRGBD { namespace Kinect1 {

/**
 * @class DrawCameraView DrawCameraView.cpp DrawCameraView.h
 * @brief Class to draw video stream from the Kinect1 data.
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class DrawCameraView : public DrawRawData
{
public:
	
	/** @brief constructor. Draw data from the video stream of the Kinect1.
	 *
	 * @param Folder [in] Main folder containing the data. Body data will be search in 'Folder/video/' subfolder.
	 * @param SizeOfFrame [in] Size of each frame. Default value =  CamWidth*CamHeight*CamBytesPerPixel.
	 */
	DrawCameraView( const std::string& Folder, int SizeOfFrame = CamWidth*CamHeight*CamBytesPerPixel )
		: DrawRawData( Folder + VideoFileName, Folder + RawVideoFileName, SizeOfFrame )
	{
		StartingFrame = 0;
	}

	/** @brief Virtual destructor, always.
	 */
	~DrawCameraView() {};

	/** @brief ProcessElement is a callback function called by mother classes when data are ready.
	 *
	 * @param RequestTimestamp [in] The timestamp of the data.
	 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
	 */
	virtual bool ProcessElement( const TimeB &RequestTimestamp, void * UserData = nullptr );
};

}} // namesapce MobileRGBD::Kinect1

#endif // KINECT_1

#ifdef KINECT_2

#include "../Kinect/KinectImageConverter.h"

namespace MobileRGBD { namespace Kinect2 {

/**
 * @class DrawCameraView DrawCameraView.cpp DrawCameraView.h
 * @brief Class to draw video stream from the Kinect2 data.
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class DrawCameraView : public DrawRawData
{
public:
	/** @brief constructor. Draw data from the video stream of the Kinect2.
	 *
	 * @param Folder [in] Main folder containing the data. Body data will be search in 'Folder/video/' subfolder.
	 * @param SizeOfFrame [in] Size of each frame. Default value = CamWidth*CamHeight*CamBytesPerPixel.
	 */
	DrawCameraView( const std::string& Folder, int SizeOfFrame = CamWidth*CamHeight*CamBytesPerPixel )
		: DrawRawData( Folder + VideoFileName, Folder + RawVideoFileName, SizeOfFrame )
	{
		StartingFrame = 0;
	}

	/** @brief Virtual destructor, always.
	 */
	~DrawCameraView() {};

	/** @brief ProcessElement is a callback function called by mother classes when data are ready.
	 *
	 * @param RequestTimestamp [in] The timestamp of the data.
	 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
	 */
	virtual bool ProcessElement( const TimeB &RequestTimestamp, void * UserData = nullptr );

protected:
	KinectImageConverter ImageConverter;		/*!< @brief Converter for the Kinect2 raw YVY2 to BRG */
};

}} // namesapce MobileRGBD::Kinect2

#endif

#endif
