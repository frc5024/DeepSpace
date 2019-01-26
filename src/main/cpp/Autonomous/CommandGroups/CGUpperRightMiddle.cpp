#include "Autonomous/CommandGroups/CGUpperRightMiddle.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDUpperRightToRightMiddle.h"

/**
 *
 */
CGUpperRightMiddle::CGUpperRightMiddle()
{
	LOG("[CGUpperRightMiddle] Constructed");

	AddSequential(new CMDUpperRightToRightMiddle());
}
