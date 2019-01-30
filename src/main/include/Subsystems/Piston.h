#ifndef _PISTON_HG_
#define _PISTON_HG_

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
#include <Commands/ControlSlider.h>
#include <frc/DoubleSolenoid.h>

class Piston : public frc::Subsystem {
 public:
  Piston(); //!< Class constructor
  void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (ControlPiston)
	
  void Deploy();  //!< Deploy the piston
  void Retract(); //!< Retract the piston
  void Release(); //!< Releases control of the piston to slide freely

 private:
  frc::DoubleSolenoid* pSolenoid; //!< Pointer to Solenoid
};

#endif //_PISTON_HG_