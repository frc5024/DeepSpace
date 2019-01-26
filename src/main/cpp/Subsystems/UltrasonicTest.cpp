

#include "Subsystems/UltrasonicTest.h"
#include "Robot.h"
#include "RobotMap.h"

UltrasonicTest::UltrasonicTest() : Subsystem("UltrasonicTest") {
  // Initialize the ultrasonic sensor:
  this->ultraSensor = new frc::Ultrasonic(1, 1); // assigns ultra to be an ultrasonic sensor which uses DigitalOutput 1 for the echo pulse and DigitalInput 1 for the trigger pulse
	this->ultraSensor->SetAutomaticMode(true); // turns on automatic mode
}

void UltrasonicTest::InitDefaultCommand() {
  SetDefaultCommand(new DriveWithJoystick()); // TODO: this should be changed}
}

double UltrasonicTest::GetDistance()
{
  return this->ultraSensor->GetRangeMM();
}