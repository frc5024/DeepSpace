#include "Commands/Actions/Crawl.h"
#include "Robot.h"

Crawl::Crawl(double speed, double timeout) : TimedCommand(timeout) {
    Requires(Robot::m_CrawlDrive);
    this->speed = speed;
}

// Called just before this Command runs the first time
void Crawl::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Crawl::Execute() {
    Robot::m_CrawlDrive->Move(this->speed);
}

// Called once after command times out
void Crawl::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Crawl::Interrupted() {}
