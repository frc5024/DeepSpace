#include "Autonomous/CommandGroups/CGCenterFrontLeft.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDCenterToFrontLeft.h"
#include "Autonomous/Commands/CMDCenterLeftToLeftStation.h"

/**
 *
 */
CGCenterFrontLeft::CGCenterFrontLeft()
{
	LOG("[CGCenterFrontLeft] Constructed");

	AddSequential(new CMDCenterToFrontLeft());
	AddSequential(new CMDCenterLeftToLeftStation());
}
