// todo: add description here later...

//#pragma once
#ifndef _ULTRASONICTEST_HG_
#define _ULTRASONICTEST_HG_

#include <frc/commands/Subsystem.h>
#include <RobotMap.h>
#include <frc/Ultrasonic.h>

class UltrasonicTest : public frc::Subsystem {
 public:
  UltrasonicTest();
  void InitDefaultCommand() override; 

  double GetDistance(); //!< Gets and returns the distance of the ultrasonic sensor.
  
 private:
  frc::Ultrasonic* ultraSensor; //!< The ultrasonic sensor used on the robot.
};
#endif // _ULTRASONICTEST_HG_