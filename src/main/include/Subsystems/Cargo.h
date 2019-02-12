#ifndef _CARGO_HG_
#define _CARGO_HG_

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
#include <Commands/ControlCargo.h>
#include <frc/DoubleSolenoid.h>
#include <frc/WPILib.h>

class Cargo : public frc::Subsystem {
 public:
  Cargo();
  void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (ControlCargo)
	
  void Deploy();  //!< Deploy the piston
  void Retract(); //!< Retract the piston
  void Release(); //!< Releases pressure from the piston

 private:
  frc::DoubleSolenoid* pSolenoid; //!< Pointer to Solenoid
};

#endif // _CARGO_HG_