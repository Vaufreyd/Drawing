/**
 * @file DrawInfraredView.cpp
 * @ingroup Drawing Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#include "DrawInfraredView.h"

#ifdef KINECT_1
	// No infrared for Kinect1
#endif


#ifdef KINECT_2

#undef min
#undef max
#include <algorithm>

// #include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace MobileRGBD { namespace Kinect2 {

/** @brief constructor. Draw data from the infrared stream of the Kinect2.
 *
 * @param Folder [in] Main folder containing the data. Body data will be search in 'Folder/infrared/' subfolder.
 * @param SizeOfFrame [in] Size of each frame. Default value = InfraredWidth*InfraredHeight*InfraredBytesPerPixel.
 */
DrawInfraredView::DrawInfraredView( const std::string& Folder, int SizeOfFrame /* = InfraredWidth*InfraredHeight*InfraredBytesPerPixel */ )
	: DrawRawData( Folder + InfraredFileName, Folder + RawInfraredFileName, SizeOfFrame )
{
	ImageBuffer = new unsigned char[DepthWidth*DepthHeight*10]; // BGR data
}

/** @brief Virtual destructor, always.
 */
DrawInfraredView::~DrawInfraredView()
{
	if ( ImageBuffer != nullptr )
	{
		delete ImageBuffer;
	}
}

/** @brief ProcessElement is a callback function called by mother classes when data are ready.
 *
 * @param RequestTimestamp [in] The timestamp of the data.
 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
 */
bool DrawInfraredView::ProcessElement( const TimeB &RequestTimestamp, void * UserData )
{
	cv::Mat& WhereToDraw = *((cv::Mat*)UserData);

	try
	{

	unsigned short int * Table = (unsigned short int*)FrameBuffer;
	int PosBuffer = 0;
	int PosRef =0;

	uchar * Img = (uchar*)ImageBuffer;

#ifdef USING_MAP
	for( int i = 0; i < DepthWidth*DepthHeight; i++, PosBuffer++ )
	{


		float originalBrightnessValue = ((float)Table[PosBuffer])/(8192.f);
 
		float amplication=1.0f;
		float gamma = .32f;
 
		// this is where the gamma and amplification levels get applied
		float gammaAppliedValue = amplication*pow(originalBrightnessValue, gamma);
		Img[PosRef++] = (uchar)(std::min(gammaAppliedValue, 1.0f)*255.0);
	}

	cv::Mat FloatImg( DepthHeight, DepthWidth, CV_8UC1, Img );
	cv::Mat MatForConversion;
	cv::applyColorMap(FloatImg, MatForConversion, cv::COLORMAP_JET);
#else
	for( int i = 0; i < DepthWidth*DepthHeight; i++, PosBuffer++ )
	{
		ImageBuffer[PosRef++] = 0;
		if ( Table[PosBuffer] == 0 )
		{
			ImageBuffer[PosRef++] = 0;
			ImageBuffer[PosRef++] = 255;
		}
		else
		{
			float originalBrightnessValue = ((float)Table[PosBuffer])/(8192.f);
 
			float amplication=1.0f;
			float gamma = .32f;
 
			// this is where the gamma and amplification levels get applied
			float gammaAppliedValue = amplication*pow(originalBrightnessValue, gamma);
 
			//here we convert it to the desired 0 - 255 range for a byte
			uchar intensity = (uchar)(std::min(gammaAppliedValue, 1.0f)*255.0);
 
			ImageBuffer[PosRef++] = (uchar)intensity;
			ImageBuffer[PosRef++] = 255;
		}
	}

	cv::Mat MatForConversion(DepthHeight, DepthWidth, CV_8UC3, ImageBuffer );

#endif

	// Resize it to finel size
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

	} catch (  cv::Exception )
	{
	}

	return true;
}

}} // namespace MobileRGBD::Kinect2

#endif	// KINECT_2
