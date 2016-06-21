/**
 * @file DrawCameraView.cpp
 * @ingroup Drawing Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#include "DrawCameraView.h"

using namespace cv;
using namespace std;

#ifdef KINECT_1

namespace MobileRGBD { namespace Kinect1 {

/** @brief ProcessElement is a callback function called by mother classes when data are ready.
 *
 * @param RequestTimestamp [in] The timestamp of the data.
 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
 */
bool DrawCameraView::ProcessElement( const TimeB &RequestTimestamp, void * UserData )
{
	cv::Mat& WhereToDraw = *((cv::Mat*)UserData);

	cv::Mat MatInit( CamHeight, CamWidth, CV_8UC4, FrameBuffer );
	cv::Mat MatForConversion( CamHeight, CamWidth, CV_8UC3 );
	// Concert color space (removing alpha channel)
	cv::cvtColor( MatInit, MatForConversion, CV_BGRA2BGR, 0 );

	// Resize it to final size
	if ( MatForConversion.rows != WhereToDraw.rows || MatForConversion.cols != WhereToDraw.cols )
	{
		cv::Mat MatForFinal( WhereToDraw.rows, WhereToDraw.cols, CV_8UC3 );
		cv::resize( MatForConversion, MatForFinal, cv::Size(WhereToDraw.cols,WhereToDraw.rows), 0, 0 );
		MatForFinal.copyTo( WhereToDraw );
	}
	else
	{
		MatForConversion.copyTo( WhereToDraw );
	}

	return true;
}

}} // namespace MobileRGBD::Kinect2

#endif

#ifdef KINECT_2

namespace MobileRGBD { namespace Kinect2 {

/* static */ KinectImageConverter DrawCameraView::ImageConverter;	

/** @brief Static function to draw data from RGB raw Kinect buffer.
 *
 */
void DrawCameraView::Draw( cv::Mat& WhereToDraw, void * FrameBuffer, int ScaleFactor )
{
	// convert it to BGR
	unsigned char * TmpFrame = ImageConverter.ConvertYVY2ToBRG((unsigned char*)FrameBuffer, Kinect2::CamWidth, Kinect2::CamHeight, ScaleFactor );
	cv::Mat MatForConversion( Kinect2::CamHeight/ScaleFactor, Kinect2::CamWidth/ScaleFactor, CV_8UC3, TmpFrame );

	// Resize it to final size
	if ( MatForConversion.rows != WhereToDraw.rows || MatForConversion.cols != WhereToDraw.cols )
	{
		cv::Mat MatForFinal( WhereToDraw.rows, WhereToDraw.cols, CV_8UC3 );
		cv::resize( MatForConversion, MatForFinal, cv::Size(WhereToDraw.cols,WhereToDraw.rows), 0, 0 );
		MatForFinal.copyTo( WhereToDraw );   
	}
	else
	{
		MatForConversion.copyTo( WhereToDraw );
	}
}

/** @brief ProcessElement is a callback function called by mother classes when data are ready.
 *
 * @param RequestTimestamp [in] The timestamp of the data.
 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
 */
bool DrawCameraView::ProcessElement( const TimeB &RequestTimestamp, void * UserData )
{
	cv::Mat& WhereToDraw = *((cv::Mat*)UserData);

	const int ScaleFactor = 2;

	// Draw it
	Draw(WhereToDraw, FrameBuffer, ScaleFactor );

	return true;
}

}} // namespace MobileRGBD::Kinect2

#endif

