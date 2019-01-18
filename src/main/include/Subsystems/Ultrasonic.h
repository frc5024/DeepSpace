// todo: add description here later...

//#pragma once
#ifndef _ULTRASONIC_HG_
#define _ULTRASONIC_HG_

#include <frc/commands/Subsystem.h>
#include <RobotMap.h>
#include <frc/Ultrasonic.h>

class Ultrasonic : public frc::Subsystem {
 public:
  Ultrasonic();
  void InitDefaultCommand() override; 

  private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  int range;
  frc::Ultrasonic* pPingwave;
  frc::Ultrasonic* pEchowave;
  frc::Ultrasonic* pMilliMeters;
};
#endif