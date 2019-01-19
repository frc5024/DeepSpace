#include "Subsystems/DriveTrain.h"
#include "Utilities/Log.h"

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain") {
  // Initialize the motors
	this->pLeftFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_FRONT_MOTOR);
	this->pLeftRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_REAR_MOTOR);
	this->pLeftRearMotor->Follow(*pLeftFrontMotor);

	this->pLeftFrontMotor->SetInverted(false);
	this->pLeftRearMotor->SetInverted(false);
	this->pLeftFrontMotor->SetNeutralMode(NeutralMode::Brake);
	this->pLeftRearMotor->SetNeutralMode(NeutralMode::Brake);

	this->pRightFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_FRONT_MOTOR);
	this->pRightRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_REAR_MOTOR);
	this->pRightRearMotor->Follow(*pRightFrontMotor);

	this->pRightFrontMotor->SetInverted(true); // change this based on test or production robot
	this->pRightRearMotor->SetInverted(true); // change this based on test or production robot
	this->pRightFrontMotor->SetNeutralMode(NeutralMode::Brake);
	this->pRightRearMotor->SetNeutralMode(NeutralMode::Brake);

  // Create a DifferentialDrive class using our motors
	this->pRobotDrive = new frc::DifferentialDrive(*pLeftFrontMotor, *pRightFrontMotor);

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
	this->pRobotDrive->ArcadeDrive(zRotation, xSpeed); // API parameter order is incorrect
	return;
}

void DriveTrain::TankDrive(double leftSpeed, double rightSpeed) {
	this->pRobotDrive->TankDrive(leftSpeed, rightSpeed);
	return;
}

/**
 *
 */
can::WPI_TalonSRX* DriveTrain::GetLeftFrontMotor()
{
	return this->pLeftFrontMotor;
}

/**
 *
 */
can::WPI_TalonSRX* DriveTrain::GetRightFrontMotor()
{
	return this->pRightFrontMotor;
}

/**
 *
 */
void DriveTrain::InitMotionProfilingMode()
{
	LOG("[DriveTrain] Motion Profiling Mode Initialized");

	this->pLeftFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, PID_LOOP_INDEX, TIMEOUT_MS);
	this->pLeftFrontMotor->SetSensorPhase(true);
	this->pLeftFrontMotor->ConfigNeutralDeadband(NEUTRAL_DEADBAND_PERCENT * 0.01, TIMEOUT_MS);

	this->pLeftFrontMotor->Config_kF(SLOT_INDEX,  0.0, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kP(SLOT_INDEX,  0.0, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kI(SLOT_INDEX,  0.0, TIMEOUT_MS);
	this->pLeftFrontMotor->Config_kD(SLOT_INDEX,  0.0, TIMEOUT_MS);

	this->pLeftFrontMotor->ConfigMotionProfileTrajectoryPeriod(10, TIMEOUT_MS); //Our profile uses 10 ms timing
	/* status 10 provides the trajectory target for motion profile AND motion magic */
	this->pLeftFrontMotor->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, TIMEOUT_MS);
	this->pLeftFrontMotor->ConfigMotionCruiseVelocity(6800, TIMEOUT_MS);
	this->pLeftFrontMotor->ConfigMotionAcceleration(6800, TIMEOUT_MS);

	this->pRightFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, PID_LOOP_INDEX, TIMEOUT_MS);
	this->pRightFrontMotor->SetSensorPhase(true);
	this->pRightFrontMotor->ConfigNeutralDeadband(NEUTRAL_DEADBAND_PERCENT * 0.01, TIMEOUT_MS);

	this->pRightFrontMotor->Config_kF(SLOT_INDEX,  0.0, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kP(SLOT_INDEX,  0.0, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kI(SLOT_INDEX,  0.0, TIMEOUT_MS);
	this->pRightFrontMotor->Config_kD(SLOT_INDEX,  0.0, TIMEOUT_MS);

	this->pRightFrontMotor->ConfigMotionProfileTrajectoryPeriod(10, TIMEOUT_MS); //Our profile uses 10 ms timing
	/* status 10 provides the trajectory target for motion profile AND motion magic */
	this->pRightFrontMotor->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, TIMEOUT_MS);
	this->pRightFrontMotor->ConfigMotionCruiseVelocity(6800, TIMEOUT_MS);
	this->pRightFrontMotor->ConfigMotionAcceleration(6800, TIMEOUT_MS);

	return;
}

/**
 *
 */
void DriveTrain::ResetDrive()
{
	// reset the motors
	this->pLeftFrontMotor->Set(ControlMode::PercentOutput, 0);
	this->pLeftRearMotor->Set(ControlMode::PercentOutput, 0);
	this->pRightFrontMotor->Set(ControlMode::PercentOutput, 0);
	this->pRightRearMotor->Set(ControlMode::PercentOutput, 0);

	this->pLeftRearMotor->Follow(*pLeftFrontMotor);
	this->pLeftFrontMotor->SetInverted(false);
	this->pLeftRearMotor->SetInverted(false);

	this->pRightRearMotor->Follow(*pRightFrontMotor);
	this->pRightFrontMotor->SetInverted(true);
	this->pRightRearMotor->SetInverted(true);

	return;
}
