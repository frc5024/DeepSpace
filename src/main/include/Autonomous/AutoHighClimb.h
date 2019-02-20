/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _AUTOHIGHCLIMB_HG_
#define _AUTOHIGHCLIMB_HG_

#include <frc/commands/CommandGroup.h>
#include "Autonomous/Actions/LowerArm.h"
#include "Autonomous/Actions/Crawl.h"
#include "Autonomous/Actions/FinishClimb.h"
#include "Autonomous/Actions/LowerLeg.h"
#include <iostream>

class AutoHighClimb : public frc::CommandGroup {
public:
	AutoHighClimb();
};

#endif /* _AUTOHIGHCLIMB_HG_ */
