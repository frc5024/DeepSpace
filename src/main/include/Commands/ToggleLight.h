/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _TOGGLELIGHT_HG_
#define _TOGGLELIGHT_HG_

#include <frc/commands/Command.h>
#include <frc/Relay.h>
#include <Subsystems/DriveTrain.h>
#include "RobotMap.h"

class ToggleLight : public frc::Command {
 public:
  ToggleLight();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

 private:
 	frc::XboxController* pJoyDrive;

  frc::Relay *lightRelay = new frc::Relay(1);
  
  bool relayState = false;
};

#endif // _TOGGLELIGHT_HG_