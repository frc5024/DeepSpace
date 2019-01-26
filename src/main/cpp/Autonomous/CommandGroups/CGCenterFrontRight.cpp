#include "Autonomous/CommandGroups/CGCenterFrontRight.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDCenterToFrontRight.h"
#include "Autonomous/Commands/CMDCenterRightToRightStation.h"

/**
 *
 */
CGCenterFrontRight::CGCenterFrontRight()
{
	LOG("[CGCenterFrontRight] Constructed");

	AddSequential(new CMDCenterToFrontRight());
	AddSequential(new CMDCenterRightToRightStation());
}
