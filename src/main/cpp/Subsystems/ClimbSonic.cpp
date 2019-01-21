#include "Subsystems/ClimbSonic.h"

ClimbSonic::ClimbSonic() : frc::Subsystem("ClimbSonic"){
  this->sensor = new Ultrasonic(1, 1);
  this->sensor->SetAutomaticMode(true);
}

void ClimbSonic::InitDefaultCommand(){
  SetDefaultCommand(new DriveWithJoystick()); // TODO: this should be changed
}

double ClimbSonic::GetDistance(){
	return this->sensor->GetRangeMM();
}
