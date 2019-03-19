#include "Subsystems/DriveTrain.h"
#include <string>

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain") {
  // Initialize the motors 
	this->pLeftFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_FRONT_MOTOR);
	this->pLeftRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_REAR_MOTOR);
	this->pLeftRearMotor->Follow(*pLeftFrontMotor);

	this->pLeftFrontMotor->SetInverted(false);
	this->pLeftRearMotor->SetInverted(false);
	// this->pLeftFrontMotor->SetNeutralMode(NeutralMode::Brake);
	// this->pLeftRearMotor->SetNeutralMode(NeutralMode::Brake);

	this->pRightFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_FRONT_MOTOR);
	this->pRightRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_REAR_MOTOR);
	this->pRightRearMotor->Follow(*pRightFrontMotor);

	this->pRightFrontMotor->SetInverted(true); // change this based on test or production robot
	this->pRightRearMotor->SetInverted(true); // change this based on test or production robot
	// this->pRightFrontMotor->SetNeutralMode(NeutralMode::Brake);
	// this->pRightRearMotor->SetNeutralMode(NeutralMode::Brake);

  // Create a DifferentialDrive class using our motors
	this->pRobotDrive = new frc::DifferentialDrive(*pLeftFrontMotor, *pRightFrontMotor);

  // Disable saftey modes
  // Sounds like a bad idea, but this prevents the robot from locking up if we take too long on a loop
	this->pLeftFrontMotor->SetSafetyEnabled(false);
	this->pLeftRearMotor->SetSafetyEnabled(false);
	this->pRightFrontMotor->SetSafetyEnabled(false);
	this->pRightRearMotor->SetSafetyEnabled(false);
	this->pRobotDrive->SetSafetyEnabled(false);

	this->pLeftFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, PID_LOOP_INDEX, TIMEOUT_MS);
	this->pLeftFrontMotor->SetSensorPhase(true);
	this->pLeftFrontMotor->ConfigNeutralDeadband(NEUTRAL_DEADBAND_PERCENT * 0.01, TIMEOUT_MS);

	this->pLeftFrontMotor->Config_kF(SLOT_INDEX, 0.0, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kP(SLOT_INDEX, 0.0, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kI(SLOT_INDEX, 0.0, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kD(SLOT_INDEX, 0.0, TIMEOUT_MS);

	this->pLeftFrontMotor->ConfigMotionProfileTrajectoryPeriod(10, TIMEOUT_MS); //Our profile uses 10 ms timing
	/* status 10 provides the trajectory target for motion profile AND motion magic */
	this->pLeftFrontMotor->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, TIMEOUT_MS);
	this->pLeftFrontMotor->ConfigMotionCruiseVelocity(6800, TIMEOUT_MS);
	this->pLeftFrontMotor->ConfigMotionAcceleration(6800, TIMEOUT_MS);

	this->pRightFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, PID_LOOP_INDEX, TIMEOUT_MS);
	this->pRightFrontMotor->SetSensorPhase(true);
	this->pRightFrontMotor->ConfigNeutralDeadband(NEUTRAL_DEADBAND_PERCENT * 0.01, TIMEOUT_MS);

	this->pRightFrontMotor->Config_kF(SLOT_INDEX, 0.0, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kP(SLOT_INDEX, 0.0, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kI(SLOT_INDEX, 0.0, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kD(SLOT_INDEX, 0.0, TIMEOUT_MS);

	this->pRightFrontMotor->ConfigMotionProfileTrajectoryPeriod(10, TIMEOUT_MS); //Our profile uses 10 ms timing
	/* status 10 provides the trajectory target for motion profile AND motion magic */
	this->pRightFrontMotor->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, TIMEOUT_MS);
	this->pRightFrontMotor->ConfigMotionCruiseVelocity(6800, TIMEOUT_MS);
	this->pRightFrontMotor->ConfigMotionAcceleration(6800, TIMEOUT_MS);
}

void DriveTrain::InitDefaultCommand() {
  SetDefaultCommand(new DriveWithJoystick());
}

void DriveTrain::ArcadeDrive(double xSpeed, double zRotation) {
	this->pRobotDrive->ArcadeDrive(zRotation, xSpeed); // API parameter order is incorrect
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

void DriveTrain::InitFollow(string path){
	
}

void DriveTrain::Follow(){
	
}