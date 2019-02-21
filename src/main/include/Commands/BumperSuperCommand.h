/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _BumperSC_HG_
#define _BumperSC_HG_

#include <frc/commands/Command.h>
#include <frc/XboxController.h>
#include "RobotMap.h"
#include <frc/GenericHID.h>

class BumperSuperCommand : public frc::Command {
 public:
  BumperSuperCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
  
 private:
  frc::XboxController* pJoyOp;
  
};


#endif