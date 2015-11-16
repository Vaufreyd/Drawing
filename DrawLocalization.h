/**
 * @file DrawLocalization.h
 * @ingroup Drawing
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @copyright All right reserved.
 */

#ifndef __DRAW_LOCALIZATION_H__
#define __DRAW_LOCALIZATION_H__

#include "DrawTimestampData.h"
#include "Drawable.h"

#define LocalisationFileName "/robulab/Localization.timestamp"	/*!< @brief Timestamp file for the localization of the robot */

namespace MobileRGBD {

/**
 * @class DrawLocalization DrawLocalization.cpp DrawLocalization.h
 * @brief Class to draw localization of the robot
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 */
class DrawLocalization : public DrawTimestampData
{
public:
	/** @brief constructor. Draw localization from the robot.
	 *
	 * @param Folder [in] Main folder containing the data. Data will be search in 'Folder/robulab/Localization.timestamp' file.
	 */
	DrawLocalization( const std::string& Folder )
		: DrawTimestampData( Folder + LocalisationFileName )
	{
	}

	/** @brief Virtual destructor, always.
	 */
	virtual ~DrawLocalization() {}

	/** @brief ProcessElement is a callback function called by mother classes when data are ready.
	 *
	 * @param RequestTimestamp [in] The timestamp of the data.
	 * @param UserData [in] User pointer to working data. Here a pointer to a cv:Mat to draw in.
	 */
	virtual bool ProcessElement(const TimeB &RequestedTimestamp, void * UserData = nullptr );
};

} // namespace MobileRGBD

#endif // __DRAW_LOCALIZATION_H__