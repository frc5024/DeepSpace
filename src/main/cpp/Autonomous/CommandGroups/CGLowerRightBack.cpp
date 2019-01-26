#include "Autonomous/CommandGroups/CGLowerRightBack.h"
#include "Utilities/Log.h"
#include "Autonomous/Commands/CMDLowerRightToRightBack.h"
#include "Autonomous/Commands/CMDRightBackToRightStation.h"
#include "Autonomous/Commands/CMDRightStationToRightMiddle.h"

/**
 *
 */
CGLowerRightBack::CGLowerRightBack()
{
	LOG("[CGLowerRight] Constructed");

	AddSequential(new CMDLowerRightToRightBack());
	AddSequential(new CMDRightBackToRightStation());
	AddSequential(new CMDRightStationToRightMiddle());
}
