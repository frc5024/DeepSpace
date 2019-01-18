/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/Ultrasonic.h"
#include "Robot.h"
#include "RobotMap.h"

Ultrasonic::Ultrasonic() : Subsystem("Ultrasonic") {
  pPingwave = new Ultrasonic(1, 0); // assigns ultra to be an ultrasonic sensor which uses DigitalOutput 1 for the echo pulse and DigitalInput 1 for the trigger pulse
	pPingwave->SetAutomaticMode(true); // turns on automatic mode

  pEchowave = new Ultrasonic(0,1);
  pEchowave->SetAutomaticMode(true);

  pMilliMeters = new Ultrasonic(0,0,1);  
}

void Ultrasonic::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  this-> DriveMode=0;
  this-> range= ultra->GetRangeMM();
  if(this->range<10)
  {
    this->DriveMode=1;
    return;
  }
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
