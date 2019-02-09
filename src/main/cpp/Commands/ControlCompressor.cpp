#include "Commands/ControlCompressor.h"
#include "Robot.h"

ControlCompressor::ControlCompressor() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::m_Compressor);
  this->pJoyOp    = Robot::m_oi->GetJoystickOperator();
  this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
}

// Called just before this Command runs the first time
// aka: every time teleop is enabled
void ControlCompressor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ControlCompressor::Execute() {
    // Enable on start button
    if(this->pJoyDrive->GetStartButtonReleased() || this->pJoyOp->GetStartButtonReleased()){
        Robot::m_Compressor->SetState(true);
    }

    // Disable on back button
    if(this->pJoyDrive->GetBackButtonReleased() || this->pJoyOp->GetBackButtonReleased()){
        Robot::m_Compressor->SetState(false);
    }
}


bool ControlCompressor::IsFinished() { return false; }

// Called once after isFinished returns true
void ControlCompressor::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ControlCompressor::Interrupted() {}
