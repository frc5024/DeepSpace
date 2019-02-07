/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//#pragma once
#ifndef _DROPCARGO_HG_
#define _DROPCARGO_HG_


#include <frc/commands/Command.h>
#include <WPILib.h>

class DropCargo : public frc::Command {
 public:
  DropCargo();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
 private:
  frc::XboxController* pCargoSwitch;
};
#endif