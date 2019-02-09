// Test command for limit switches. TOOD: Delete later since limit switches won't be used on the robot.

#include "iostream"
#include "Commands/LimitSwitchCommand.h"
#include "Robot.h"

LimitSwitchCommand::LimitSwitchCommand() {
  Requires(Robot::m_liSwitches);
}

// Called just before this Command runs the first time
void LimitSwitchCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void LimitSwitchCommand::Execute() {
  // Test code for the limit switch #1:
  bool test1 = Robot::m_liSwitches->isOn1();
  // std::cout << "The value of limit switch #1 is: " << test1 << "(" << Robot::m_liSwitches->ChannelNumber() << ")" << std::endl;

  // // Test code for the limit switch #1:
  // bool test2 = Robot::m_liSwitches->isOn2();
  // std::cout << "value of limit switch #2 is" << test2 << std::endl;
  //std::cout << "The Value of the Hall effect is :" << test1 << std::endl;
  
}

// Make this return true when this Command no longer needs to run execute()
bool LimitSwitchCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void LimitSwitchCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LimitSwitchCommand::Interrupted() {}