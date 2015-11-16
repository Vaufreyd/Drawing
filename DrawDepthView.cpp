/**
 * @file DrawDepthView.cpp
 * @ingroup Drawing Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#include "DrawDepthView.h"

#undef min
#include <algorithm>

#ifdef KINECT_1

namespace MobileRGBD { namespace Kinect1 {

/** @brief ProcessElement is a callback function called by mother classes when data are ready.
 *
 * @param RequestTimestamp [in] The timestamp of the data.
 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
 */
bool DrawDepthView::ProcessElement( const TimeB &RequestTimestamp, void * UserData /* = nullptr */ )
{
	cv::Mat& WhereToDraw = *((cv::Mat*)UserData);

	try
	{
		ushort * ImageBuffer2 = (ushort*)FrameBuffer;
	
		// Remove player detection information (cause noisy depth)
		const int LineSize = 640;
		for( int line = 0; line < 480; line++ )
		{
			for( int col = 0; col < 640; col++ )
			{
				Users[line][col] = (uchar)(ImageBuffer2[line*LineSize+col] & 0x07);
				ImageBuffer2[line*LineSize+col] = ImageBuffer2[line*LineSize+col] >> 3;
			}
		}

		cv::Mat MatInit( 480, 640, CV_16UC1, FrameBuffer );
		cv::Mat MatScaled( 480, 640, CV_8UC1 );
		cv::Mat MatForConversion( 480, 640, CV_8UC3 );

		MatInit.convertTo( MatScaled, 1.0/16.0, 0.0 );

		// Concert color space
		cvtColor( MatScaled, MatForConversion, CV_GRAY2BGR, 0 );

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

}} // namespace MobileRGBD::Kinect1


#endif // KINECT_1


#ifdef KINECT_2

namespace MobileRGBD { namespace Kinect2 {

/** @brief ProcessElement is a callback function called by mother classes when data are ready.
 *
 * @param RequestTimestamp [in] The timestamp of the data.
 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
 */
bool DrawDepthView::ProcessElement( const TimeB &RequestTimestamp, void * UserData /* = nullptr */ )
{
	cv::Mat& WhereToDraw = *((cv::Mat*)UserData);

	try
	{
		unsigned short int * Table = (unsigned short int*)FrameBuffer;
		int PosBuffer = 0;
		int PosRef = 0;

		for( int i = 0; i < DepthWidth*DepthHeight; i++, PosBuffer++ )
		{
			if ( Table[PosBuffer] == 0 )
			{
				ImageBuffer[PosRef++] = 0;
				ImageBuffer[PosRef++] = 0;
				ImageBuffer[PosRef++] = 0;
			}
			else
			{
				float originalBrightnessValue = ((float)Table[PosBuffer])/(65536.f);
 
				float amplication=1.0f;
				float gamma = .32f;
 
				// this is where the gamma and amplification levels get applied
				float gammaAppliedValue = amplication*pow(originalBrightnessValue, gamma);
 
				// here we convert it to the desired 0 - 255 range for a byte
				uchar intensity = (uchar)(std::min((float)gammaAppliedValue, 1.0f)*255.0f);
 
				ImageBuffer[PosRef++] = intensity;
				ImageBuffer[PosRef++] = intensity;
				ImageBuffer[PosRef++] = intensity;
			}
		}

		cv::Mat MatForConversion(DepthHeight, DepthWidth, CV_8UC3, ImageBuffer );

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


#endif // KINECT_2

