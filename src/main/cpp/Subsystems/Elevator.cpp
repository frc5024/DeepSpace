/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Subsystems/Elevator.h>



Elevator::Elevator() : Subsystem("Elevator Subsystem") {
  

}

void Elevator::InitDefaultCommand() {
  SetDefaultCommand(new MoveElevator());
}

void Elevator::setSpeed(double speed){
  this->pElevatorMotor->Set(speed);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
