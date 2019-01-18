/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _TURNANGLE_HG_
#define _TURNANGLE_HG_

#include <frc/commands/Command.h>
#include <Subsystems/DriveTrain.h>
#include <iostream>
#include <RobotMap.h>
#include <AHRS.h>
#include <frc/Timer.h>
#include <networktables/NetworkTable.h>

class TurnAngle : public frc::Command {
 public:
  TurnAngle();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

  void SetTarget(float angle) ;
  void Go(void) ;
  void Stop(void) ;
  void Turn(void) ;

private:
  float target ;
	AHRS* m_pGryo; //!< Pointer to the navX○
	frc::Timer* m_pTimer; //!< A timer for timing things
	frc::XboxController* pJoyDrive; //!< A pointer for the network table
	std::shared_ptr<NetworkTable> table; //!< A pointer to the /SmartDashboard/Vision table
};

#endif // _TURNANGLE_HG_