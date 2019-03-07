//! A subsystem that interfaces the green light on the robot
#ifndef _LIGHT_HG_
#define _LIGHT_HG_

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
#include <Commands/ControlLight.h>
#include <frc/Solenoid.h>

class Light : public frc::Subsystem {
 public:
  Light(); //!< Class constructor
  void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (ControlLight)
	
  void On(); //!< Turns the green light on
  void Off(); //!< Turns the green light off

 private:
  frc::Solenoid* pLight; //!< Pointer to Solenoid
};

#endif //_LIGHT_HG_