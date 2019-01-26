#include "Autonomous/CommandGroups/CGLowerLeftMiddle.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDLowerLeftToLeftMiddle.h"

/**
 *
 */
CGLowerLeftMiddle::CGLowerLeftMiddle()
{
	LOG("[CGLowerLeftMiddle] Constructed");

	AddSequential(new CMDLowerLeftToLeftMiddle());
}
