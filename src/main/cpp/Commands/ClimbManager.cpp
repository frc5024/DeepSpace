#include "Commands/ClimbManager.h"
#include "Robot.h"
#include <iostream>
#include <frc/commands/Scheduler.h>

ClimbManager::ClimbState ClimbManager::CurrentClimbState;

ClimbManager::ClimbManager() {
	this->pJoyOp = Robot::m_oi->GetJoystickOperator();
	this->CurrentClimbState = this->ClimbState::kInactive;
}

// Called just before this Command runs the first time
void ClimbManager::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimbManager::Execute() {

    // If operator is holding left on D-pad and hits the left trigger
    if ( (this->pJoyOp->GetPOV() == 270) &&  (this->pJoyOp->GetStickButtonPressed(GenericHID::kRightHand)) ) {

        // If we're already running Auto climb
        if (ClimbManager::CurrentClimbState == ClimbManager::kAuto) {

            // Cancel the auto climb
            ClimbManager::CurrentClimbState = ClimbManager::kInactive;
            UpdateRumble();

        } else {

            // Otherwise, Start auto climb command
            ClimbManager::CurrentClimbState = ClimbManager::kAuto;
            UpdateRumble();
        }
    } 
    // If operator is holding right on D-pad and hits the left trigger
    else if ( (this->pJoyOp->GetPOV() == 90) &&  (this->pJoyOp->GetStickButtonPressed(GenericHID::kRightHand)) ) {
        
        // If we're already in manual climb mode
        if (ClimbManager::CurrentClimbState == ClimbManager::kActive) {

            // Stop manual climb
            ClimbManager::CurrentClimbState = ClimbManager::kInactive;
            UpdateRumble();

        } else {

            // Otherwise, Start manual climb commands
            ClimbManager::CurrentClimbState = ClimbManager::kActive;
            UpdateRumble();
        }
    }
}

// Make this return true when this Command no longer needs to run execute()
bool ClimbManager::IsFinished() {}

// Called once after isFinished returns true
void ClimbManager::End() {

    // Good measure
    ClimbManager::CurrentClimbState = ClimbManager::ClimbState::kInactive ;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbManager::Interrupted() {

    // Good measure
    ClimbManager::CurrentClimbState = ClimbManager::ClimbState::kInactive ;
}

void ClimbManager::UpdateRumble() {

    // Reset rumble, since we know it's changing
    this->pJoyOp->SetRumble(frc::GenericHID::RumbleType::kLeftRumble,  0.0);
    this->pJoyOp->SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0.0);
    
    // Rumble depending on which mode we're in
    switch(ClimbManager::CurrentClimbState) {
        case ClimbManager::kAuto:
            this->pJoyOp->SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 0.5);
            break;
        case ClimbManager::kActive:
            this->pJoyOp->SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0.5);
            break;
        default:
            break;
    }
}
