#include "Subsystems/CrawlDrive.h"

CrawlDrive::CrawlDrive() : frc::Subsystem("CrawlDrive") {
    //Initialize the motors
    this->pCrawlLeft  = new frc::Spark(CRAWL_LEFT_MOTOR);

    this->pCrawlLeft->SetInverted(false);
    //this->pCrawlLeft->SetNeutralMode(NeutralMode::Brake);

    this->pCrawlRight = new frc::Spark(CRAWL_RIGHT_MOTOR);
    this->pCrawlRight->SetInverted(true);
    //this->pCrawlRight->SetNeutralMode(NeutralMode::Brake);

    // Disable saftey modes
    // Sounds like a bad idea, but this prevents the robot from lockingup if we take too long on a loop
    this->pCrawlLeft->SetSafetyEnabled(false);
    this->pCrawlRight->SetSafetyEnabled(false);

}

void CrawlDrive::InitDefaultCommand() {
    //SetDefaultCommand(new DriveWithJoystick());
}

void CrawlDrive::Move(double Speed) {
	this->pCrawlRight->Set(Speed);
    this->pCrawlLeft->Set(Speed);
	return;
}
