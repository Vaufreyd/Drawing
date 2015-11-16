/**
 * @file DrawBodyIndexView.cpp
 * @ingroup Drawing Kinect
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#include "DrawBodyIndexView.h"

#ifdef KINECT_2

namespace MobileRGBD { namespace Kinect2 {

/*!< @brief shared BRG color index for body drawing. First body will always have the sale color, etc. */
unsigned char DrawBodyIndexView::Colors[6][3] = {
		{ 255, 0, 0 },
		{ 0, 255, 0 },
		{ 0, 0, 255 },
		{ 255, 255, 0},
		{ 255, 0, 255},
		{ 0, 255, 255}
};

/** @brief constructor. Draw data from the Body stream of the Kinect2.
 *
 * @param Folder [in] Main folder containing the data. Body data will be search in 'Folder/body_index/' subfolder.
 * @param SizeOfFrame [in] Size of each frame. Default value = DepthWidth*DepthHeight (1 byte per pixel).
 */
DrawBodyIndexView::DrawBodyIndexView( const std::string& Folder, int SizeOfFrame /* = DepthWidth*DepthHeight */ )
	: DrawRawData( Folder + BodyIndexFileName, Folder + RawBodyIndexFileName, SizeOfFrame )
{
	ImageBuffer = new unsigned char[DepthWidth*DepthHeight*3]; // BGR data
}

/** @brief Virtual destructor, always.
 */
DrawBodyIndexView::~DrawBodyIndexView()
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
bool DrawBodyIndexView::ProcessElement( const TimeB &RequestTimestamp, void * UserData )
{
	cv::Mat& WhereToDraw = *((cv::Mat*)UserData);

	try
	{

	char * Table = (char*)FrameBuffer;
	int PosBuffer = 0;
	int PosRef =0;
	cv::Vec3b Pixel;
	for( int i = 0; i < DepthWidth*DepthHeight; i++, PosBuffer++ )
	{
		if ( Table[PosBuffer] < 0 || Table[PosBuffer] > 5 )
		{
			ImageBuffer[PosRef++] = 0;
			ImageBuffer[PosRef++] = 0;
			ImageBuffer[PosRef++] = 0;
		}
		else
		{
			ImageBuffer[PosRef++] = Colors[Table[PosBuffer]][0];
			ImageBuffer[PosRef++] = Colors[Table[PosBuffer]][1];
			ImageBuffer[PosRef++] = Colors[Table[PosBuffer]][2];
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

// Remove file name defines
#undef BodyIndexFileName
#undef RawBodyIndexFileName

}} // namespace MobileRGBD::Kinect2

#endif	// KINECT_2
