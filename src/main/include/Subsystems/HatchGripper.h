//! A subsystem that interfaces the hatch gripper on the robot
#ifndef _HATCHGRIPPER_HG_
#define _HATCHGRIPPER_HG_

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
#include <Commands/ControlHatchGripper.h>
#include <frc/DoubleSolenoid.h>
#include <frc/WPILib.h>

class HatchGripper : public frc::Subsystem {
 public:
  HatchGripper(); //!< Class constructor
  void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (ControlHatchGripper)
	
  void Deploy();  //!< Deploy the gripper
  void Retract(); //!< Retract the gripper
  void TurnOff(); //!< Turn of gripper

 private:
  frc::DoubleSolenoid* pHatchSolenoid; //!< Pointer to double solenoid
};

#endif //_HATCHGRIPPER_HG_