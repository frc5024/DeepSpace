//! A command for testing the ultrasonic sensor
#ifndef _TESTULTRA_HG_
#define _TESTULTRA_HG_

#include <frc/commands/Command.h>
#include <Subsystems/DriveTrain.h>
#include <Subsystems/Arm.h>
#include "RobotMap.h"
#include <frc/GenericHID.h>

class testUltra : public frc::Command {
 public:
  testUltra();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};

#endif //_TESTULTRA_HG_