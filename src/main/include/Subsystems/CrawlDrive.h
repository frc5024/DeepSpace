//! A subsytem that interfaces with the climberbase on the robot
#ifndef _CRAWLDRIVE_HG_
#define _CRAWLDRIVE_HG_

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "RobotMap.h"
#include <frc/drive/DifferentialDrive.h>

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
    void ArcadeDrive(double xSpeed, double zRotation);

    private:
    can::WPI_TalonSRX* pCrawlLeft; //!< Pointer for the left crawl motor
    can::WPI_TalonSRX* pCrawlRight; //!< Pointer for the right craw motor

    frc::DifferentialDrive* pCrawlDriveTrain; //!< Pointer for a differential drivebase made up of 2 motors
};

#endif // _CRAWLDRIVE_HG_