#include "Autonomous/CommandGroups/CGUpperRightBack.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDUpperRightToRightBack.h"
#include "Autonomous/Commands/CMDRightBackToRightStation.h"
#include "Autonomous/Commands/CMDRightStationToRightMiddle.h"

/**
 *
 */
CGUpperRightBack::CGUpperRightBack()
{
	LOG("[CGUpperRight] Constructed");

	AddSequential(new CMDUpperRightToRightBack());
	AddSequential(new CMDRightBackToRightStation());
	AddSequential(new CMDRightStationToRightMiddle());
}
