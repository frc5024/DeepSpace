//#pragma once
#ifndef _ULTRASONICDISTANCE_HG_
#define _ULTRASONICDISTANCE_HG_

#include <frc/commands/Subsystem.h>
#include <RobotMap.h>
#include <frc/Ultrasonic.h>

class UltrasonicDistance : public frc::Subsystem {
 public:
  UltrasonicDistance();
  void InitDefaultCommand() override; 

  double GetDistance(); //!< Gets and returns the distance of the ultrasonic sensor
  
 private:
  frc::Ultrasonic* ultraSensor; //!< The ultrasonic sensor used on the robot
};
#endif // _ULTRASONICDISTANCE_HG_