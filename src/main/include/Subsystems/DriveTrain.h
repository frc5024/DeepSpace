//! A subsystem that interfaces with the drivebase on the robot
#ifndef _DRIVETRAIN_HG_
#define _DRIVETRAIN_HG_

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <frc/drive/DifferentialDrive.h>
#include "RobotMap.h"
#include <Commands/DriveWithJoystick.h>
#include <string>
#include <pathfinder.h>

class DriveTrain : public frc::Subsystem {
 public:
  DriveTrain(); //!< Class constructor
  void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (DriveWithJoystick)
	
	/**
	 * Pass data to wpilib's ArcadeDrive
	 *
	 * @param xSpeed Forward speed (form -1 to 1)
	 * @param zRotation Rotation (from -1 to 1)
	 */
  void ArcadeDrive(double xSpeed, double zRotation);
  
  /**
   * Passes data to wpilib's TankDrive
   *
   * @param leftSpeed left motor speed
   * @param rightSpeed right motor speed
   */
	void TankDrive(double leftSpeed, double rightSpeed);
	
	/**
	 * Drive with circles
	 *
	 * @param magnitude Magnitude modifier for the radius output
	 * @param radial Value that is computed into the outside motor's basic output
	 */
	void RadialDrive(double magnitude, double radial);

	/**
	 * Follow path specified
	 * @param path name
	 */
	void InitFollow(string path);
	void Follow();

  private:
	can::WPI_TalonSRX *pLeftFrontMotor; //!< Pointer for left front motor
	can::WPI_TalonSRX* pLeftRearMotor;  //!< Pointer for left rear motor
	can::WPI_TalonSRX* pRightFrontMotor;//!< Pointer for right front motor
	can::WPI_TalonSRX* pRightRearMotor; //!< Pointer for right rear motor

	frc::DifferentialDrive* pRobotDrive; //!< Pointer for a differential drivebase made up of 2 motor pairs
};

#endif // _DRIVETRAIN_HG_