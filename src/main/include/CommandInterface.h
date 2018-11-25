//! The base class for all commands

#pragma once

#include "Subsystems/DriveTrain.h"
#include "OI.h"
#include <WPILib.h>
#include "Commands/Command.h"

class CommandInterface: public frc::Command {
public:
	CommandInterface();	//!< Class constructor

	static OI* pOI;	
	static DriveTrain* pDriveTrain;
};


