#include "Subsystems/DriveTrain.h"

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain") {
  // Initialize the motors
	this->pLeftFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_FRONT_MOTOR);
	this->pLeftRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_REAR_MOTOR);
	this->pLeftRearMotor->Follow(*pLeftFrontMotor);

	// this->pLeftFrontMotor->SetInverted(true);
	// this->pLeftRearMotor->SetInverted(true);
	

	this->pRightFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_FRONT_MOTOR);
	this->pRightRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_REAR_MOTOR);
	this->pRightRearMotor->Follow(*pRightFrontMotor);

	// this->pRightFrontMotor->SetInverted(true); // change this based on test or production robot
	// this->pRightRearMotor->SetInverted(true); // change this based on test or production robot
	
	this->pLeftFrontMotor->SetNeutralMode(NeutralMode::Brake);
	this->pLeftRearMotor->SetNeutralMode(NeutralMode::Brake);

	this->pRightFrontMotor->SetNeutralMode(NeutralMode::Brake);
	this->pRightRearMotor->SetNeutralMode(NeutralMode::Brake);

  // Create a DifferentialDrive class using our motors
	this->pRobotDrive = new frc::DifferentialDrive(*pLeftFrontMotor, *pRightFrontMotor);

  // Disable saftey modes
  // Sounds like a bad idea, but this prevents the robot from locking up if we take too long on a loop
	// this->pLeftFrontMotor->SetSafetyEnabled(false);
	// this->pLeftRearMotor->SetSafetyEnabled(false);
	// this->pRightFrontMotor->SetSafetyEnabled(false);
	// this->pRightRearMotor->SetSafetyEnabled(false);
	this->pRobotDrive->SetSafetyEnabled(false);

	// Create the Arcade controller
	this->pArcadeController = new rr::PIDController(ARCADE_KP, ARCADE_KI, ARCADE_KD);

	// Configure encoders
	this->pLeftFrontMotor->ConfigFactoryDefault();
	this->pRightFrontMotor->ConfigFactoryDefault();

	this->pLeftFrontMotor->SetSensorPhase(true);
	this->pRightFrontMotor->SetSensorPhase(true);

	this->pRightFrontMotor->SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, 10);
	this->pRightFrontMotor->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, 10);

	/* Set the peak and nominal outputs */
	this->pRightFrontMotor->ConfigNominalOutputForward(0, 10);
	this->pRightFrontMotor->ConfigNominalOutputReverse(0, 10);
	this->pRightFrontMotor->ConfigPeakOutputForward(1, 10);
	this->pRightFrontMotor->ConfigPeakOutputReverse(-1, 10);

	/* Set Motion Magic gains in slot0 - see documentation */
	this->pRightFrontMotor->SelectProfileSlot(0, 0);
	this->pRightFrontMotor->Config_kF(0, 0.3, 10);
	this->pRightFrontMotor->Config_kP(0, 0.1, 10);
	this->pRightFrontMotor->Config_kI(0, 0.0, 10);
	this->pRightFrontMotor->Config_kD(0, 0.0, 10);

	/* Set acceleration and vcruise velocity - see documentation */
	this->pRightFrontMotor->ConfigMotionCruiseVelocity(1500, 10);
	this->pRightFrontMotor->ConfigMotionAcceleration(1500, 10);


	this->pLeftFrontMotor->SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, 10);
	this->pLeftFrontMotor->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, 10);

	/* Set the peak and nominal outputs */
	this->pLeftFrontMotor->ConfigNominalOutputForward(0, 10);
	this->pLeftFrontMotor->ConfigNominalOutputReverse(0, 10);
	this->pLeftFrontMotor->ConfigPeakOutputForward(1, 10);
	this->pLeftFrontMotor->ConfigPeakOutputReverse(-1, 10);

	/* Set Motion Magic gains in slot0 - see documentation */
	this->pLeftFrontMotor->SelectProfileSlot(0, 0);
	this->pLeftFrontMotor->Config_kF(0, 0.3, 10);
	this->pLeftFrontMotor->Config_kP(0, 0.1, 10);
	this->pLeftFrontMotor->Config_kI(0, 0.0, 10);
	this->pLeftFrontMotor->Config_kD(0, 0.0, 10);

	/* Set acceleration and vcruise velocity - see documentation */
	this->pLeftFrontMotor->ConfigMotionCruiseVelocity(1500, 10);
	this->pLeftFrontMotor->ConfigMotionAcceleration(1500, 10);
}

void DriveTrain::InitDefaultCommand() {
  SetDefaultCommand(new DriveWithJoystick());
}

void DriveTrain::ArcadeDrive(double xSpeed, double zRotation) {
	// double speed = this->pArcadeController->Feed(xSpeed, (this->pLeftFrontMotor->GetSelectedSensorVelocity()));
	this->pRobotDrive->ArcadeDrive(xSpeed, zRotation);
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

void DriveTrain::RawDrive(double l, double r){
	this->pLeftFrontMotor->Set(l);
	this->pRightFrontMotor->Set(r);
}

void DriveTrain::Coast(){
	this->pLeftFrontMotor->SetNeutralMode(NeutralMode::Coast);
	this->pLeftRearMotor->SetNeutralMode(NeutralMode::Coast);

	this->pRightFrontMotor->SetNeutralMode(NeutralMode::Coast);
	this->pRightRearMotor->SetNeutralMode(NeutralMode::Coast);
}

void DriveTrain::Break(){
	this->pLeftFrontMotor->SetNeutralMode(NeutralMode::Brake);
	this->pLeftRearMotor->SetNeutralMode(NeutralMode::Brake);

	this->pRightFrontMotor->SetNeutralMode(NeutralMode::Brake);
	this->pRightRearMotor->SetNeutralMode(NeutralMode::Brake);
}

void DriveTrain::MagicDrive(double left, double right, double magnitude){
	this->pLeftFrontMotor->Set(ControlMode::MotionMagic, left * TALLON_TPR * magnitude);
	this->pRightFrontMotor->Set(ControlMode::MotionMagic, right * TALLON_TPR * magnitude);
	std::cout << left * TALLON_TPR * magnitude << " | " << right * TALLON_TPR * magnitude << std::endl;
	std::cout << this->pLeftFrontMotor->GetClosedLoopError(0) << " | " << this->pRightFrontMotor->GetClosedLoopError(0) << std::endl;
}