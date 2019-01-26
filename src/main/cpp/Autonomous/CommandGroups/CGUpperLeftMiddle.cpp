#include "Autonomous/CommandGroups/CGUpperLeftMiddle.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDUpperLeftToLeftMiddle.h"

/**
 *
 */
CGUpperLeftMiddle::CGUpperLeftMiddle()
{
	LOG("[CGUpperLeftMiddle] Constructed");

	AddSequential(new CMDUpperLeftToLeftMiddle());
}
