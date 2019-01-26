#include "Autonomous/CommandGroups/CGUpperRightFront.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDUpperRightToRightFront.h"

/**
 *
 */
CGUpperRightFront::CGUpperRightFront()
{
	LOG("[CGUpperRightFront] Constructed");

	AddSequential(new CMDUpperRightToRightFront());
}
