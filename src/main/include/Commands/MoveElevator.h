/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#ifndef _MOVE_ELEVATOR_HG
#define _MOVE_ELEVATOR_HG

#include <Commands/Command.h>
#include <Subsystems/Elevator.h>
#include <WPILib.h>

class MoveElevator : public frc::Command {
 public:
  MoveElevator();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
 private:
  double pos;
  double neg;
  double speed;
  frc::XboxController* pJoyDrive;
};

#endif //endit