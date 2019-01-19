#include "Autonomous/CommandGroups/CGJustDriveForward.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDJustDriveForward.h"

/**
 *
 */
CGJustDriveForward::CGJustDriveForward()
{
	LOG("[CGJustDriveForward] Constructed");

	AddSequential(new CMDJustDriveForward());
}
