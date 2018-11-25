#include "CommandInterface.h"

// static variables in C++ have to be declared here
// (not in the .hpp file)
DriveTrain* CommandInterface::pDriveTrain = NULL;
OI* CommandInterface::pOI = NULL;

CommandInterface::CommandInterface() : Command() {

	if (CommandInterface::pOI == nullptr) {
		CommandInterface::pOI = new OI();
	}

	if (CommandInterface::pDriveTrain == nullptr) {
		CommandInterface::pDriveTrain = new DriveTrain();
	}

	return;
}
