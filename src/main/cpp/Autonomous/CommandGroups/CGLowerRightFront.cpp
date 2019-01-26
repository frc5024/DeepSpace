#include "Autonomous/CommandGroups/CGLowerRightFront.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDLowerRightToRightFront.h"

/**
 *
 */
CGLowerRightFront::CGLowerRightFront()
{
	LOG("[CGLowerRightFront] Constructed");

	AddSequential(new CMDLowerRightToRightFront());
}
