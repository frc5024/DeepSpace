#include "Commands/Actions/Crawl.h"
#include "Robot.h"

Crawl::Crawl(double speed, double timeout) : TimedCommand(timeout) {
    Requires(Robot::m_CrawlDrive);
    this->speed = speed;
    this->onFloor = Robot::m_CrawlDrive->GetSensor() ;
}

// Called just before this Command runs the first time
void Crawl::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Crawl::Execute() {
    Robot::m_CrawlDrive->Move(this->speed);
}

bool Crawl::IsFinished(void)
{
    bool newState = Robot::m_CrawlDrive->GetSensor() ;
    if ( ! this->onFloor) {
        if (newState)
            // If we went from the air to the ground, we're there
            return true ;
    } else {
        // Update state
        this->onFloor = newState ;
    }
    return false ;
}

// Called once after command times out
void Crawl::End() {
    Robot::m_CrawlDrive->Move(0.0) ;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Crawl::Interrupted() {
    Robot::m_CrawlDrive->Move(0.0) ;
}
