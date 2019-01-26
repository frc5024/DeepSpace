#include "Autonomous/CommandGroups/CGUpperLeftFront.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDUpperLeftToLeftFront.h"

/**
 *
 */
CGUpperLeftFront::CGUpperLeftFront()
{
	LOG("[CGUpperLeftFront] Constructed");

	AddSequential(new CMDUpperLeftToLeftFront());
}
