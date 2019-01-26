#include "Autonomous/CommandGroups/CGLowerLeftBack.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDLowerLeftToLeftBack.h"
#include "Autonomous/Commands/CMDLeftBackToLeftStation.h"
#include "Autonomous/Commands/CMDLeftStationToLeftMiddle.h"

/**
 *
 */
CGLowerLeftBack::CGLowerLeftBack()
{
	LOG("[CGLowerLeft] Constructed");

	AddSequential(new CMDLowerLeftToLeftBack());
	AddSequential(new CMDLeftBackToLeftStation());
	AddSequential(new CMDLeftStationToLeftMiddle());
}
