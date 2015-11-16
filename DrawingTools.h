/**
 * @file DrawingTools.h
 * @ingroup Drawing
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAWING_TOOLS_H__
#define __DRAWING_TOOLS_H__

#include <stdio.h>
#include <string>

namespace MobileRGBD {

/** @brief Rule of three computation for a coordinate conversion in pixel mode.
 *
 * @param Coordinate [in] Coordinate to convert in pixel.
 * @param NbPixelMax [in] Nombre of pixel on this axe.
 * @param HalfDistance [in] Scaling information. HaklDistance correponds to half of pixels
 */
inline int CoordonateToPixel( double Coordinate, int NbPixelMax, double HalfDistance = 10.0 )
{
	// 0 => VideoWidth/2
	// HalfDistance => NbPixelMax

	int lCount = (int)(Coordinate*(double)NbPixelMax/HalfDistance);

	return lCount;
}

/** @brief Rule of three computation for a coordinate conversion in pixel mode. Centering
 *         is done adding half of the NbPixelMax.
 *
 * @param Coordinate [in] Coordinate to convert in pixel.
 * @param NbPixelMax [in] Nombre of pixel on this axe.
 * @param HalfDistance [in] Scaling information. HaklDistance correponds to half of pixels
 */
inline int CoordonateToPixelCentered( double Coordinate, int NbPixelMax, double HalfDistance = 10.0 )
{
	// 0 => VideoWidth/2
	// HalfDistance => NbPixelMax

	int lCount = CoordonateToPixel(Coordinate, NbPixelMax, HalfDistance) + NbPixelMax/2;

	return lCount;
}

/** @brief Specific computation for the Y axis of a centered Y coordinate. "Centering" is done at
 *         NbPixelMax/2 + NbPixelMax/6 pixels.
 *
 * @param Coordinate [in] Coordinate to convert in pixel.
 * @param NbPixelMax [in] Nombre of pixel on this axe.
 * @param HalfDistance [in] Scaling information. HaklDistance correponds to half of pixels
 */
inline int Y_CoordonateToPixelCentered( double Coordinate, int NbPixelMax, double HalfDistance = 10.0 )
{
	// 0 => VideoWidth/2
	// HalfDistance => NbPixelMax

	int lCount = CoordonateToPixel(Coordinate, NbPixelMax, HalfDistance) + NbPixelMax/2 + NbPixelMax/6;

	return lCount;
}

/** @brief Specific computation for the X axis of a centered X coordinate. Centering is done at
 *         NbPixelMax/2 pixels.
 *
 * @param Coordinate [in] Coordinate to convert in pixel.
 * @param NbPixelMax [in] Nombre of pixel on this axe.
 * @param HalfDistance [in] Scaling information. HaklDistance correponds to half of pixels
 */
inline int X_CoordonateToPixelCentered( double Coordinate, int NbPixelMax, double HalfDistance = 10 )
{
	// 0 => VideoWidth/2
	// HalfDistance => NbPixelMax

	int lCount = CoordonateToPixel(Coordinate, NbPixelMax, HalfDistance) + NbPixelMax/2;

	return lCount;
}

} // namespace MobileRGBD

#endif // __DRAWING_TOOLS_H__