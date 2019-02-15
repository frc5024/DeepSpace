#ifndef _Flap_HG_
#define _Flap_HG_

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
#include <Commands/ControlSlider.h>
#include <frc/DoubleSolenoid.h>

class Flap : public frc::Subsystem {
 public:
  Flap(); //!< Class constructor
  void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (ControlFlap)
	
  void Deploy();  //!< Deploy the Flap
  void Retract(); //!< Retract the Flap
  void Release(); //!< Release pressure

 private:
  frc::DoubleSolenoid* pSolenoid; //!< Pointer to Solenoid
};

#endif //_Flap_HG_