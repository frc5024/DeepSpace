//! A subsystem that interfaces with the robot's flap that holds and releases the cargo
#ifndef _Flap_HG_
#define _Flap_HG_

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
#include <Commands/ControlCargo.h>
#include <frc/DoubleSolenoid.h>

class Flap : public frc::Subsystem {
 public:
  Flap(); //!< Class constructor
  void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (ControlFlap)
	
  void Deploy();  //!< Deploy the flap
  void Retract(); //!< Retract the flap
  void Release(); //!< Release pressure

 private:
  frc::DoubleSolenoid* pSolenoid; //!< Pointer to Solenoid
};

#endif //_Flap_HG_