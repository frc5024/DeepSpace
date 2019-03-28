#include "Subsystems/DriveTrain.h"
#include <iostream>

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain") {
  // Initialize the motors
	this->pLeftFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_FRONT_MOTOR);
	this->pLeftRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_REAR_MOTOR);
	this->pLeftRearMotor->Follow(*pLeftFrontMotor);

	this->pLeftFrontMotor->SetInverted(true);
	this->pLeftRearMotor->SetInverted(true);
	// this->pLeftFrontMotor->SetNeutralMode(NeutralMode::Coast);
	// this->pLeftRearMotor->SetNeutralMode(NeutralMode::Coast);

	this->pRightFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_FRONT_MOTOR);
	this->pRightRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_REAR_MOTOR);
	this->pRightRearMotor->Follow(*pRightFrontMotor);

	this->pRightFrontMotor->SetInverted(true); // change this based on test or production robot
	this->pRightRearMotor->SetInverted(true); // change this based on test or production robot
	// this->pRightFrontMotor->SetNeutralMode(NeutralMode::Coast);
	// this->pRightRearMotor->SetNeutralMode(NeutralMode::Coast);

  // Create a DifferentialDrive class using our motors
	this->pRobotDrive = new frc::DifferentialDrive(*pLeftFrontMotor, *pRightFrontMotor);

  // Disable saftey modes
  // Sounds like a bad idea, but this prevents the robot from locking up if we take too long on a loop
	// this->pLeftFrontMotor->SetSafetyEnabled(false);
	// this->pLeftRearMotor->SetSafetyEnabled(false);
	// this->pRightFrontMotor->SetSafetyEnabled(false);
	// this->pRightRearMotor->SetSafetyEnabled(false);
	this->pRobotDrive->SetSafetyEnabled(false);

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

	this->pGyro = new AHRS(frc::SPI::kMXP);
  this->pGyro->Reset();
}

void DriveTrain::InitDefaultCommand() {
  SetDefaultCommand(new DriveWithJoystick());
	this->ResetLeft();
	this->ResetRight();
}

void DriveTrain::ArcadeDrive(double xSpeed, double zRotation) {
	this->pRobotDrive->ArcadeDrive(xSpeed, zRotation); // API parameter order is incorrect
	// std::cout << "Left: " << this->GetLeftTicks() << " Right: " << this->GetRightTicks() << std::endl;
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

int DriveTrain::GetLeftTicks(){
	return this->pLeftFrontMotor->GetSelectedSensorPosition();
}

int DriveTrain::GetRightTicks(){
	return this->pRightFrontMotor->GetSelectedSensorPosition();
}

void DriveTrain::ResetLeft(){
	this->pLeftFrontMotor->SetSelectedSensorPosition(0, 0, 10);
}

void DriveTrain::ResetRight(){
	this->pRightFrontMotor->SetSelectedSensorPosition(0, 0, 10);
}

void DriveTrain::MagicDrive(double left, double right, double magnitude){
	this->pLeftFrontMotor->Set(ControlMode::MotionMagic, left * TALLON_TPR * magnitude);
	this->pRightFrontMotor->Set(ControlMode::MotionMagic, right * TALLON_TPR * magnitude);
	std::cout << left * TALLON_TPR * magnitude << " | " << right * TALLON_TPR * magnitude << std::endl;
	std::cout << this->pLeftFrontMotor->GetClosedLoopError(0) << " | " << this->pRightFrontMotor->GetClosedLoopError(0) << std::endl;
}

void DriveTrain::RawDrive(double l, double r){
	this->pLeftFrontMotor->Set(l);
	this->pRightFrontMotor->Set(r);
}

TankProfile* DriveTrain::LoadProfile(const char * name){
	// const char *path = "/home/lvuser/deploy/paths/" + name;
	Log("Config PID");
	double P = 0.0;
	double I = 0.0;
	double D = 0.0;
	double A = 2.0;

	Log("Build TankProfile");
	// Create a TankProfile to return
	TankProfile *output = (TankProfile*) malloc(sizeof(TankProfile));
	

	// Over-sized Trajectory to store raw input
	Segment trajectory[1024];
	memset(trajectory, 0, sizeof(Segment) * 1024);

	// Load the file
	Log("Opening left csv");
	Log(name);
	FILE *fp = fopen(name, "r");
	output->length = pathfinder_deserialize_csv(fp, trajectory);
	fclose(fp);
// malloc()
	// output->leftTrajectory  = (Segment*) malloc(sizeof(Segment) * output->length);
	// if (output->leftTrajectory == nullptr)
	// 	Log("It bad.");
	// output->rightTrajectory = (Segment*) malloc(sizeof(Segment) * output->length);
	// if (output->leftTrajectory == nullptr)
	// 	Log("It bad 2.");

	// *(output->leftTrajectory + output->length) = NULL;

	memset(output->leftTrajectory, 0, sizeof(Segment) * output->length);
	memset(output->rightTrajectory, 0, sizeof(Segment) * output->length);


	// Parse left and right sides
	pathfinder_modify_tank(trajectory, output->length, output->leftTrajectory, output->rightTrajectory, ROBOT_WIDTH);

	// Create encoder configs
	output->leftConfig = {
			this->GetLeftTicks(),
			TALLON_TPR,
			WHEEL_CIRC,
			P,
			I,
			D,
			1.0 / MAX_VELOCITY,
			A
	};

	output->rightConfig = {
			this->GetRightTicks(),
			TALLON_TPR,
			WHEEL_CIRC,
			P,
			I,
			D,
			1.0 / MAX_VELOCITY,
			A
	};

	output->leftFollower.finished = 0;
	output->leftFollower.segment = 0;

	output->rightFollower.finished = 0;
	output->rightFollower.segment = 0;

	return output;
}

void DriveTrain::ResetProfile(TankProfile *profile){
	// Goto first point
	profile->leftFollower.segment = 0;
	profile->rightFollower.segment = 0;

	// Set finished to false
	profile->leftFollower.finished = 0;
	profile->rightFollower.finished = 0;
}

void DriveTrain::Follow(TankProfile *profile){
	if(profile->leftFollower.finished && profile->rightFollower.finished){
		Log(profile->length);
		return;
	}
	// Get motor speeds for point
	// std::cout << "config: " << sizeof(profile->leftConfig) << " follower: " << sizeof(profile->leftFollower) << " trajectory: " << sizeof(profile->leftTrajectory) << std::endl;
	double l = pathfinder_follow_encoder(profile->leftConfig, &profile->leftFollower, profile->leftTrajectory, profile->length, this->GetLeftTicks());
	// Log("Built left speed");
	double r = pathfinder_follow_encoder(profile->rightConfig, &profile->rightFollower, profile->rightTrajectory, profile->length, this->GetRightTicks());

	// find gyro error
	Log("Converting gyro to output");
	double gyro_heading = this->pGyro->GetAngle();
  	double desired_heading = r2d(profile->leftFollower.heading);
	double angle_difference = desired_heading - gyro_heading;

	// wrap angle around 360
	angle_difference = std::fmod(angle_difference, 360.0);
	if (std::abs(angle_difference) > 180.0) {
		angle_difference = (angle_difference > 0) ? angle_difference - 360 : angle_difference + 360;
	}

	// Get amount to turn
	double turn = 0.8 * (-1.0/80.0) * angle_difference;

	// drive
	this->RawDrive(l + turn, r - turn);
}