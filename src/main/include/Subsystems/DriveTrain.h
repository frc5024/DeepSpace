/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <Drive/DifferentialDrive.h>
#include "RobotMap.h"

class DriveTrain : public frc::Subsystem {
 public:
  DriveTrain();
  void InitDefaultCommand() override;

  void ArcadeDrive(double xSpeed, double zRotation);
	void TankDrive(double leftSpeed, double rightSpeed);

 private:
  can::WPI_TalonSRX* pLeftFrontMotor;
	can::WPI_TalonSRX* pLeftRearMotor;
	can::WPI_TalonSRX* pRightFrontMotor;
	can::WPI_TalonSRX* pRightRearMotor;

	frc::DifferentialDrive* pRobotDrive;
};
