/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/Timer.h"

Timer::Timer() : Subsystem("ExampleSubsystem") {}

void Timer::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
int Timer::startTime(){
  start = clock();
  return start;
}
int Timer::elapsed(){
  end = clock();
  return end;
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
