/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#ifndef _INTAKE_HG_
#define _INTAKE_HG_

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "RobotMap.h"
#include <Commands/MoveIntake.h>

class Intake : public frc::Subsystem {
 private:
  can::WPI_TalonSRX* pIntakeR;
  can::WPI_TalonSRX* pIntakeL;
  

 public:
  Intake();
  void InitDefaultCommand() override;
  void setSpeed(double speed);
};

#endif //end me