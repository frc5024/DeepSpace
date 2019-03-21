#include "Subsystems/DriveTrain.h"
#include "DeviceMap.h"
#include <iostream>


/* DriveTrain */
DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain") {
  // Initialize the motors
	this->pLeftFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_FRONT_MOTOR);
	this->pLeftRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_REAR_MOTOR);

	this->pLeftFrontMotor->SetInverted(false);
	this->pLeftRearMotor->SetInverted(false);

	this->pRightFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_FRONT_MOTOR);
	this->pRightRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_REAR_MOTOR);

	this->pRightFrontMotor->SetInverted(false);
	this->pRightRearMotor->SetInverted(false);

  // Create a DifferentialDrive class using our motors
	this->pLeftGearBox->motor = new frc::SpeedControllerGroup(*this->pLeftFrontMotor, *this->pLeftRearMotor);
	this->pLeftGearBox->sensor = new rr::components::TalonAdapter(this->pLeftFrontMotor, WHEEL_CIRCUM_CM, TALLON_TPR, false);
	this->pLeftGearBox->sensor->Reset();

	this->pRightGearBox->motor = new frc::SpeedControllerGroup(*this->pRightFrontMotor, *this->pRightRearMotor);
	this->pRightGearBox->sensor = new rr::components::TalonAdapter(this->pRightFrontMotor, WHEEL_CIRCUM_CM, TALLON_TPR, true);

	this->pRobotDrive = new frc::DifferentialDrive(*this->pLeftGearBox->motor, *this->pRightGearBox->motor);

  // Disable saftey modes
  // Sounds like a bad idea, but this prevents the robot from locking up if we take too long on a loop
	this->pLeftFrontMotor->SetSafetyEnabled(false);
	this->pLeftRearMotor->SetSafetyEnabled(false);
	this->pRightFrontMotor->SetSafetyEnabled(false);
	this->pRightRearMotor->SetSafetyEnabled(false);
	this->pRobotDrive->SetSafetyEnabled(false);
}

void DriveTrain::InitDefaultCommand() {
  SetDefaultCommand(new DriveWithJoystick());
}

void DriveTrain::ArcadeDrive(double xSpeed, double zRotation) {
	this->pRobotDrive->ArcadeDrive(xSpeed, zRotation); // Pass through to robot drive
	// The following line is for debugging encoders
	// std::cout << "Left: " << this->pLeftGearBox->sensor->GetTicks() << " Right: " << this->pRightGearBox->sensor->GetTicks() << std::endl;
	return;
}

void DriveTrain::TankDrive(double leftSpeed, double rightSpeed) {
	this->pRobotDrive->TankDrive(leftSpeed, rightSpeed);
	return;
}

void DriveTrain::RadialDrive(double magnitude, double radial){
  // set the speeds
  double leftSpeed, rightSpeed = 0;
  
  // asign the right motor speed
  rightSpeed = magnitude;
  
  // Calculate the radial
  radial += (radial > 1)? 1 : -1;
  radial *= (fabs(magnitude) > DRIVETRAIN_RADIAL_SENSITIVITY_CUTOFF)? 1 : DRIVEWITHJOYSTICK_ROTATION_LIMITER;
  
  // calculate left speed
  leftSpeed = rightSpeed * radial;
  
  // pass to tankdrive
  this->pRobotDrive->TankDrive(leftSpeed, rightSpeed);
  return;
}

int DriveTrain::GetLeftEncoderPosition(){
	return this->pLeftGearBox->sensor->GetTicks();
}

int DriveTrain::GetRightEncoderPosition(){
	return this->pRightGearBox->sensor->GetTicks();
}