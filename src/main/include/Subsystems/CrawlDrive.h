//! A subsytem that interfaces with the climberbase on the robot
#ifndef _CRAWLDRIVE_HG_
#define _CRAWLDRIVE_HG_

#include <frc/commands/Subsystem.h>
#include <frc/DigitalInput.h>
#include <frc/WPILib.h>
#include <frc/Spark.h>
#include "RobotMap.h"

class CrawlDrive: public frc::Subsystem {
    public:
     CrawlDrive(); //!< Class constructor
     void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem () 

    /**
	 * Pass data to wpilib's ArcadeDrive
	 *
	 * @param xSpeed Forward speed (form -1 to 1)
	 * @param zRotation Rotation (from -1 to 1)
	 */
    void Move(double Speed);

    /**
     * @brief Returns true if its on the floor
     * 
     * @return true Something is right in front of it (on the floor)
     * @return false Nothing in front of it (in the air)
     */
    bool GetSensor(void) ;

private:
    frc::Spark* pCrawlLeft; //!< Pointer for the left crawl motor
    frc::Spark* pCrawlRight; //!< Pointer for the right crawl motor
    frc::DigitalInput* pFloorSensor;
};

#endif // _CRAWLDRIVE_HG_