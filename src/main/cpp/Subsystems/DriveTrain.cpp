#include "Subsystems/DriveTrain.h"

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


	/* choose the sensor and sensor direction */
	pLeftFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, PID_LOOP_INDEX, TIMEOUT_MS);
	pLeftFrontMotor->SetSensorPhase(false);

	/* set the peak and nominal outputs, 12V means full */
	pLeftFrontMotor->ConfigNominalOutputForward(0, TIMEOUT_MS);
	pLeftFrontMotor->ConfigNominalOutputReverse(0, TIMEOUT_MS);
	pLeftFrontMotor->ConfigPeakOutputForward(1, TIMEOUT_MS);
	pLeftFrontMotor->ConfigPeakOutputReverse(-1, TIMEOUT_MS);

	/* set closed loop gains in slot0 */
	pLeftFrontMotor->Config_kP(PID_LOOP_INDEX, 0.5, TIMEOUT_MS);
	pLeftFrontMotor->Config_kI(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);
	pLeftFrontMotor->Config_kD(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);
	pLeftFrontMotor->Config_kF(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);

//	int absLeftPosition = pLeftFrontMotor->GetSelectedSensorPosition(SLOT_INDEX) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
	int abLeftPosition = this->pLeftFrontMotor->GetSensorCollection().GetPulseWidthPosition();
	this->pLeftFrontMotor->SetSelectedSensorPosition(abLeftPosition, PID_LOOP_INDEX, TIMEOUT_MS);

	pRightFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, PID_LOOP_INDEX, TIMEOUT_MS);
	pRightFrontMotor->SetSensorPhase(false);

	/* set the peak and nominal outputs, 12V means full */
	pRightFrontMotor->ConfigNominalOutputForward(0, TIMEOUT_MS);
	pRightFrontMotor->ConfigNominalOutputReverse(0, TIMEOUT_MS);
	pRightFrontMotor->ConfigPeakOutputForward(1, TIMEOUT_MS);
	pRightFrontMotor->ConfigPeakOutputReverse(-1, TIMEOUT_MS);

	/* set closed loop gains in slot0 */
	pRightFrontMotor->Config_kP(PID_LOOP_INDEX, 0.5, TIMEOUT_MS);
	pRightFrontMotor->Config_kI(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);
	pRightFrontMotor->Config_kD(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);
	pRightFrontMotor->Config_kF(PID_LOOP_INDEX, 0.0, TIMEOUT_MS);

//	int abRightPosition = this->pRightFrontMotor->GetSelectedSensorPosition(SLOT_INDEX) & 0xFFF;
	int abRightPosition = this->pRightFrontMotor->GetSensorCollection().GetPulseWidthPosition();
	this->pRightFrontMotor->SetSelectedSensorPosition(abRightPosition, PID_LOOP_INDEX, TIMEOUT_MS);


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

void DriveTrain::RadialDrive(double magnitude, double radial) {
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

void DriveTrain::ResetEncoders(void) {
	this->pLeftFrontMotor->SetSelectedSensorPosition(0, PID_LOOP_INDEX, TIMOUT_MS) ;
	this->pLeftRearMotor->SetSelectedSensorPosition(0, PID_LOOP_INDEX, TIMOUT_MS) ;
	this->pRightFrontMotor->SetSelectedSensorPosition(0, PID_LOOP_INDEX, TIMOUT_MS) ;
	this->pRightRearMotor->SetSelectedSensorPosition(0, PID_LOOP_INDEX, TIMOUT_MS) ;
	
	return ;
}

void DriveTrain::ResetLeftEncoder(void) {
	this->pLeftFrontMotor->SetSelectedSensorPosition(0, PID_LOOP_INDEX, TIMOUT_MS) ;
	this->pLeftRearMotor->SetSelectedSensorPosition(0, PID_LOOP_INDEX, TIMOUT_MS) ;
	
	return ;
}

void DriveTrain::ResetRightEncoder(void) {
	this->pRightFrontMotor->SetSelectedSensorPosition(0, PID_LOOP_INDEX, TIMOUT_MS) ;
	this->pRightRearMotor->SetSelectedSensorPosition(0, PID_LOOP_INDEX, TIMOUT_MS) ;
	
	return ;
}

float DriveTrain::GetDistance(void) {
	float retr  = this->pLeftFrontMotor->GetSelectedSensorPosition(SLOT_INDEX)
				+ this->pRightFrontMotor->GetSelectedSensorPosition(SLOT_INDEX)
				+ this->pLeftRearMotor->GetSelectedSensorPosition(SLOT_INDEX)
				+ this->pLeftFrontMotor->GetSelectedSensorPosition(SLOT_INDEX) ;
	return (retr / 4.0 / TICKS_PER_REVOLUTION * WHEEL_CIRCUMFERENCE) ;
}

float DriveTrain::GetDistanceQuick(void) {
	return this->pRightFrontMotor->GetSelectedSensorPosition(SLOT_INDEX) / TICKS_PER_REVOLUTION * WHEEL_CIRCUMFERENCE ;
}

float DriveTrain::GetLeftDistance(void) {
	float retr  = this->pLeftFrontMotor->GetSelectedSensorPosition(SLOT_INDEX)
				+ this->pLeftRearMotor->GetSelectedSensorPosition(SLOT_INDEX) ;
	return (retr / 2.0 / TICKS_PER_REVOLUTION * WHEEL_CIRCUMFERENCE) ;
}

float DriveTrain::GetRightDistance(void) {
	float retr  = this->pRightFrontMotor->GetSelectedSensorPosition(SLOT_INDEX)
				+ this->pRightRearMotor->GetSelectedSensorPosition(SLOT_INDEX) ;
	return (retr / 2.0 / TICKS_PER_REVOLUTION * WHEEL_CIRCUMFERENCE) ;
}

float DriveTrain::GetLeftDistanceQuick(void) {
	return this->pLeftFrontMotor->GetSelectedSensorPosition(SLOT_INDEX) / TICKS_PER_REVOLUTION * WHEEL_CIRCUMFERENCE ;
}

float DriveTrain::GetRightDistanceQuick(void) {
	return this->pRightFrontMotor->GetSelectedSensorPosition(SLOT_INDEX) / TICKS_PER_REVOLUTION * WHEEL_CIRCUMFERENCE ;
}
