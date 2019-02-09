// Test command to see if the hall effect sensor works or not

#include "iostream"
#include "Commands/HallEffectTest.h"
#include "Robot.h"

HallEffectTest::HallEffectTest() {
  Requires(Robot::m_hEffect);
}

// Called just before this Command runs the first time
void HallEffectTest::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HallEffectTest::Execute() {
  bool test1 = Robot::m_hEffect->nearMagnet1();
  std::cout << "The value of the first hall effect sensor is: " << test1 << std::endl;

  // Test code for the limit switch #1:
  //bool test2 = Robot::hEffect->nearMagnet1();
  // std::cout << "The value of the first hall effect sensor is: " << test2 << std::endl;
}

// Make this return true when this Command no longer needs to run execute()
bool HallEffectTest::IsFinished() { return false; }

// Called once after isFinished returns true
void HallEffectTest::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HallEffectTest::Interrupted() {}
