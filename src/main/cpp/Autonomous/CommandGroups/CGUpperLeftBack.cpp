#include "Autonomous/CommandGroups/CGUpperLeftBack.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDUpperLeftToLeftBack.h"
#include "Autonomous/Commands/CMDLeftBackToLeftStation.h"
#include "Autonomous/Commands/CMDLeftStationToLeftMiddle.h"

/**
 *
 */
CGUpperLeftBack::CGUpperLeftBack()
{
	LOG("[CGUpperLeft] Constructed");

	AddSequential(new CMDUpperLeftToLeftBack());
	AddSequential(new CMDLeftBackToLeftStation());
	AddSequential(new CMDLeftStationToLeftMiddle());
}
