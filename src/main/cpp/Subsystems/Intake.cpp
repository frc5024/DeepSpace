/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Subsystems/Intake.h>

Intake::Intake() : Subsystem("ExampleSubsystem") {
  
}

void Intake::InitDefaultCommand() {
  SetDefaultCommand(new MoveIntake());
}

void Intake::setSpeed(double speed){
  this->pIntakeL->Set(speed);
  this->pIntakeR->Set(speed);
  
}
