/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/Lighting.h"
#include <iostream>

Lighting::Lighting() : Subsystem("Lighting") {
  this->pLightController = new frc::Spark(LEDCONTROLLER_ID);
}

void Lighting::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Lighting::Set(LedColour colour){
  std::cout << "LED COLOUR: " << colour / (double)100 << std::endl;
  this->pLightController->Set(colour / (double)100);
}
