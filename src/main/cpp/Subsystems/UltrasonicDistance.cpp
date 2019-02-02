#include "Subsystems/UltrasonicDistance.h"
#include "Robot.h"
#include "RobotMap.h"

UltrasonicDistance::UltrasonicDistance() : Subsystem("UltrasonicDistance") {
  // Initialize the ultrasonic sensor:
  this->ultraSensor = new frc::Ultrasonic(ULTRASONIC_PORT, ULTRASONIC_PORT); // assigns ultra to be an ultrasonic sensor which uses DigitalOutput 1 for the echo pulse and DigitalInput 1 for the trigger pulse
	this->ultraSensor->SetAutomaticMode(true); // turns on automatic mode
}

void UltrasonicDistance::InitDefaultCommand() {
  SetDefaultCommand(new DriveWithJoystick()); // TODO: this should be changed}
}

double UltrasonicDistance::GetDistance()
{
  return this->ultraSensor->GetRangeMM();
}