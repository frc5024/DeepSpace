//! A subsystem that interfaces with the drivebase on the robot
#ifndef _DRIVETRAIN_HG_
#define _DRIVETRAIN_HG_

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <Encoder.h>
#include <frc/drive/DifferentialDrive.h>
#include "RobotMap.h"
#include <Commands/DriveWithJoystick.h>

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
	 * @brief Resets all encoder sensor positions to 0
	 */
	void ResetEncoders(void);

	/**
	 * @brief Resets the left side encoder sensor positions to 0
	 */
	void ResetLeftEncoder(void);

	/**
	 * @brief Resets the right side encoder sensor positions to 0
	 */
	void ResetRightEncoder(void);

	/**
	 * @brief Get's the average of all encoder values in cm
	 * @return Distance delta in centimetres
	 */
	float GetDistance(void) ;

	/**
	 * @brief Gets the distance of ONLY the FRONT RIGHT motor
	 * @remark Only uses FRONT RIGHT motor
	 * @remark Equivalent to GetRightDistanceQuick(void)
	 * @return Distance delta in centimetres
	 */
	float GetDistanceQuick(void) ;

	/**
	 * @brief Get's the average of all left side encoder values in cm
	 * @return Distance delta in centimetres
	 */
	float GetLeftDistance(void) ;

	/**
	 * @brief Get's the average of all right side encoder values in cm
	 * @return Distance delta in centimetres
	 */
	float GetRightDistance(void) ;

	/**
	 * @brief Gets the distance of ONLY the FONT LEFT motor
	 * @remark Only uses the FRONT LEFT motor
	 * @return Distance delta in centimetres
	 */
	float GetLeftDistanceQuick(void) ;

	/**
	 * @brief Gets the distance of ONLY the FONT RIGHT motor
	 * @remark Only uses the FRONT RIGHT motor
	 * @remark Equivalent to GetDistanceQuick(void)
	 * @return Distance delta in centimetres
	 */
	float GetRightDistanceQuick(void) ;

 private:
	can::WPI_TalonSRX* pLeftFrontMotor; //!< Pointer for left front motor
	can::WPI_TalonSRX* pLeftRearMotor;  //!< Pointer for left rear motor
	can::WPI_TalonSRX* pRightFrontMotor;//!< Pointer for right front motor
	can::WPI_TalonSRX* pRightRearMotor; //!< Pointer for right rear motor

	frc::DifferentialDrive* pRobotDrive; //!< Pointer for a differential drivebase made up of 2 motor pairs

};

#endif // _DRIVETRAIN_HG_