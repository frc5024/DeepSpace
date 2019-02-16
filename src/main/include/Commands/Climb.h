/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _CLIMB_HG_
#define _CLIMB_HG_

#include <frc/commands/CommandGroup.h>

// Acions
#include <Commands/Actions/Crawl.h>
#include <Commands/Actions/HoldArms.h>
#include <Commands/Actions/HoldLegs.h>
#include <Commands/Actions/MoveLegsTo.h>
#include <Commands/Actions/RaiseArms.h>
#include <Commands/Actions/RaiseLegs.h>
#include <Commands/Actions/Drive.h>
#include <Commands/Actions/EndClimb.h>

class Climb : public frc::CommandGroup {
 public:
  Climb();
};

#endif /* _CLIMB_HG_ */
