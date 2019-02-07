/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/Cargo.h"
#include "RobotMap.h"

Cargo::Cargo() : Subsystem("ExampleSubsystem") {
  this->pCargoSolenoid = new frc::Solenoid(CARGO_SOLENOID);

}

void Cargo::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());

  //SetDefaultCommand(new );
  return;
}

void Cargo::ExtendCargo(bool on){
  this->pCargoSolenoid->Set(on);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
