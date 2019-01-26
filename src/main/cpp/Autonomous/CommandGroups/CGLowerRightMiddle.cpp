#include "Autonomous/CommandGroups/CGLowerRightMiddle.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDLowerRightToRightMiddle.h"

/**
 *
 */
CGLowerRightMiddle::CGLowerRightMiddle()
{
	LOG("[CGLowerRightMiddle] Constructed");

	AddSequential(new CMDLowerRightToRightMiddle());
}
