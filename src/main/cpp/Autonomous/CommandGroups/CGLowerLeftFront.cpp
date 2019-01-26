#include "Autonomous/CommandGroups/CGLowerLeftFront.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDLowerLeftToLeftFront.h"

/**
 *
 */
CGLowerLeftFront::CGLowerLeftFront()
{
	LOG("[CGLowerLeftFront] Constructed");

	AddSequential(new CMDLowerLeftToLeftFront());
}
