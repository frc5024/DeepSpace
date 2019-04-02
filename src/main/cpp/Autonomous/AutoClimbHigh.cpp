/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Autonomous/AutoClimbHigh.h"
#include "Robot.h"

AutoClimbHigh::AutoClimbHigh() {
	Requires(Robot::m_Arm);
	Requires(Robot::m_Leg);
	Requires(Robot::m_CrawlDrive);
	Requires(Robot::m_DriveTrain);
	this->pTimer = new frc::Timer();
	this->stage = S_LOWER_ARM;
	this->onFloor = true;
    this->climbing = false;
}

void AutoClimbHigh::Initialize() {
    this->climbing = true;
	this->stage = S_LOWER_ARM;
	this->onFloor = true;
	this->pTimer->Reset();
	this->pTimer->Start();
}

void AutoClimbHigh::Execute() {
	// Execute the appropriate function for the current stage of climb
    switch (this->stage) {
        case S_LOWER_ARM : this->Execute_LowerArm() ; break;
        case S_LOWER_LEG : this->Execute_LowerLeg() ; break;
        case S_CRAWL	 : this->Execute_Crawl()	; break;
        case S_DRIVE	 : this->Execute_Drive()	; break;
        case S_RAISE_LEG : this->Execute_Raiseleg() ; break;
        case S_FINISHED  : return;
        default :
            Log("AutoClimbHigh has an invalid stage") ;
            this->stage = S_FINISHED ;
            break;
    }
}

void AutoClimbHigh::Execute_LowerArm(void) {

    // Moves arm from 35% to 100% throughout 1 seconds, then caps at 100%
	float speed = 0.4 + std::min(this->pTimer->Get(), 1.0) * 0.60 ;
    Robot::m_Arm->MoveArm(speed);

	// If arm is lowered or it's been 5 seconds, go to next stage
	if (Robot::m_Arm->GetSensor()
	||  this->pTimer->Get() > 3.0) {
		this->stage = S_LOWER_LEG;
		this->pTimer->Reset();
	}
}

void AutoClimbHigh::Execute_LowerLeg(void) {

	Robot::m_Arm->MoveArm(ARM_HOLD_SPEED);  // Keep arm down
	Robot::m_Leg->MoveLeg(-1.0);            // Bring leg down

	// If leg is at bottom or it's been 6 seconds, go to the next stage
	if (Robot::m_Leg->AtBottom()
	||  this->pTimer->Get() > 10.0) {
		this->stage = S_CRAWL;
		this->pTimer->Reset();
	}
}

void AutoClimbHigh::Execute_Crawl(void) {

	Robot::m_Arm->MoveArm(ARM_HOLD_SPEED);      // Keep arm down
	Robot::m_Leg->MoveLeg(LEG_HOLD_SPEED);      // Keep leg down
	Robot::m_CrawlDrive->Move(1.0);             // Crawl forward
	Robot::m_DriveTrain->ArcadeDrive(0.6, 0.0); // Drive forward

	// Get if we are NOW on the floor
	bool nowOnFloor = Robot::m_CrawlDrive->GetSensor();

	// If we were in the air and are now on the floor, go to the next stage
	if (!this->onFloor && nowOnFloor) {
		this->stage = S_DRIVE;
		this->pTimer->Reset();
	} else {
		// Otherwise update our 'were' with our 'now'
		this->onFloor = nowOnFloor ;
	}

	// Or, if it's been 6 seconds, go to the next stage
	if (this->pTimer->Get() > 6.0) {
		this->stage = S_DRIVE;
		this->pTimer->Reset();
	}
}

void AutoClimbHigh::Execute_Drive(void) {

	Robot::m_Arm->MoveArm(-0.25);           // Bring arm up slowly
	Robot::m_Leg->MoveLeg(LEG_HOLD_SPEED);  // Keep leg down
	Robot::m_CrawlDrive->Move(0.0);         // Brake the crawlDrive

    // Drives from 60% to 20% throughout 2 seconds then flatlines at 20%
    double power = 0.6 - std::min(this->pTimer->Get(), 2.0) * 0.2 ;
    Robot::m_DriveTrain->ArcadeDrive(power, 0.0);

	// We do this for only 2.1 seconds, no sensors for this part
	if (this->pTimer->Get() > 2.1) {
		this->stage = S_RAISE_LEG;
		this->pTimer->Reset();
        Robot::m_DriveTrain->ArcadeDrive(-0.3, 0.0);
	}
}

void AutoClimbHigh::Execute_Raiseleg(void) {

	Robot::m_Arm->MoveArm(0.0);                 // Brake
	Robot::m_DriveTrain->TankDrive(0.0,0.0);    // Brake
	Robot::m_Leg->MoveLeg(1.0);                 // Bring legs back up

	// If leg is at top or it's been 3.2 seconds, we are finished
	if (Robot::m_Leg->AtTop()
	||	this->pTimer->Get() > 3.2) {
		this->stage = S_FINISHED ;
	}	
}

bool AutoClimbHigh::IsFinished() {

    // Stop if we're no longer in auto climb mode
    if (ClimbManager::CurrentClimbState != ClimbManager::kAuto) {
        return true;
    }

    // Stop if we've reached the end of the climb process
    if (this->stage == S_FINISHED) {
        
        // cannot change climbState in above scenario, hence why we change it here and not in End()
        ClimbManager::CurrentClimbState = ClimbManager::kInactive;

        return true;
    }
    return false;
}

void AutoClimbHigh::End() {
	// Brake all subsystems and stop timer
	Robot::m_Arm->MoveArm(0.0);
	Robot::m_Leg->MoveLeg(0.0);
	Robot::m_DriveTrain->TankDrive(0.0, 0.0);
	Robot::m_CrawlDrive->Move(0.0);
    this->pTimer->Stop();
    this->climbing = false;
}

void AutoClimbHigh::Interrupted() {
    // Brake all subsystems and stop timer
	Robot::m_Arm->MoveArm(0.0);
	Robot::m_Leg->MoveLeg(0.0);
	Robot::m_DriveTrain->TankDrive(0.0, 0.0);
	Robot::m_CrawlDrive->Move(0.0);
    this->pTimer->Stop();
    this->climbing = false;
}

bool AutoClimbHigh::IsClimbing() {
    return this->climbing;
}
