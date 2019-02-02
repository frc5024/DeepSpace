// Test command for limit switches. TOOD: Delete later since limit switches won't be used on the robot.

#include "iostream"
#include "Commands/TestCommand.h"
#include "Robot.h"

TestCommand::TestCommand() {
  Requires(Robot::liSwitches);
}

// Called just before this Command runs the first time
void TestCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TestCommand::Execute() {
  // Test code for the limit switch #1:
  bool test1 = Robot::liSwitches->isOn1();
  std::cout << "The value of limit switch #1 is: " << test1 << "(" << Robot::liSwitches->ChannelNumber() << ")" << std::endl;

  // Test code for the limit switch #1:
  bool test2 = Robot::liSwitches->isOn2();
  std::cout << "The value of limit switch #2 is" << test2 << std::endl;
}

// Make this return true when this Command no longer needs to run execute()
bool TestCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void TestCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestCommand::Interrupted() {}