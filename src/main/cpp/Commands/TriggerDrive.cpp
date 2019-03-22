#include "Commands/TriggerDrive.h"
#include "Robot.h"

TriggerDrive::TriggerDrive() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::m_DriveTrain);
  this->pJoyDrive = Robot::m_oi->GetJoystickDrive();
}

// Called just before this Command runs the first time
// aka: every time teleop is enabled
void TriggerDrive::Initialize() {
  // Set speed and direction multipliers
  this->directionMultiplier = 1;
  this->speedMultiplier     = 1;

  //set Speed and Rotation
  this->speed    = 0.0;
  this->rotation = 0.0;

  // Load test profile
  Log("Load file");
  FILE *fp = fopen("/home/lvuser/deploy/paths/Unnamed.pf1.csv", "r");
  this->legnth = pathfinder_deserialize_csv(fp, this->trajectory);
  fclose(fp);

  // gen
  Log("Mod tank");
  
  pathfinder_modify_tank(this->trajectory, this->legnth, this->leftTrajectory, this->rightTrajectory, this->wheelbase_width);

  Log("Config");
  this->configL = { Robot::m_DriveTrain->GetLeftTicks(), TALLON_TPR, 0.638,      // Position, Ticks per Rev, Wheel Circumference
                         1.0, 0.0, 0.0, 0.1 / 3, 0.0};
  this->configR = { Robot::m_DriveTrain->GetRightTicks(), TALLON_TPR, 0.638,      // Position, Ticks per Rev, Wheel Circumference
                         1.0, 0.0, 0.0, 0.10 / 3, 0.0};

  Log("Gyro");
  this->pGyro = new AHRS(frc::SPI::kMXP);
  this->pGyro->Reset();

}

// Called repeatedly when this Command is scheduled to run
void TriggerDrive::Execute() {
  // Deal with reversing and slow mode
	this->directionMultiplier *= (this->pJoyDrive->GetXButtonReleased())? -1 : 1;
  this->speedMultiplier      = (this->pJoyDrive->GetBumper(Hand::kRightHand)) ? 0.6 : 1;

  // Get movement data form controller
  // Speed = Right trigger - left trigger
  this->speed = (this->pJoyDrive->GetTriggerAxis(Hand::kRightHand) - this->pJoyDrive->GetTriggerAxis(Hand::kLeftHand));
	this->rotation = this->pJoyDrive->GetX(Hand::kLeftHand);
	
	// Multiply each value with it's multiplier(s)
  this->speed    *= (this->speedMultiplier * this->directionMultiplier);
  this->rotation *= (this->speedMultiplier * DRIVEWITHJOYSTICK_ROTATION_LIMITER);

  // Robot::m_DriveTrain->ArcadeDrive(this->speed, this->rotation);

  // Test MagicDrive
  // Robot::m_DriveTrain->MagicDrive(
  //     this->pJoyDrive->GetY(Hand::kLeftHand) * -1,
  //     this->pJoyDrive->GetY(Hand::kRightHand) * -1,
  //     1
  //     );

  // Log("l/r");
  if(this->pJoyDrive->GetAButton()){
    // pathfinder_modify_tank(this->trajectory, this->legnth, this->leftTrajectory, this->rightTrajectory, this->wheelbase_width);
    this->followerL.segment = 0;
    this->followerL.finished = 0;
    this->followerR.segment = 0;
    this->followerR.finished = 0;
  }
  if(this->pJoyDrive->GetBButton()){
    double l = pathfinder_follow_encoder(this->configL, &this->followerL, this->leftTrajectory, this->legnth, Robot::m_DriveTrain->GetLeftTicks());
    double r = pathfinder_follow_encoder(this->configR, &this->followerR, this->rightTrajectory, this->legnth, Robot::m_DriveTrain->GetRightTicks());

    // Log("Angles");
    double gyro_heading = this->pGyro->GetAngle();
    double desired_heading = r2d(this->followerL.heading);

    // Log("Diff");
    double angle_difference = desired_heading - gyro_heading;

    angle_difference = std::fmod(angle_difference, 360.0);
    if (std::abs(angle_difference) > 180.0) {
      angle_difference = (angle_difference > 0) ? angle_difference - 360 : angle_difference + 360;
    }

    // Log("Turn");
    double turn = 0.8 * (-1.0/80.0) * angle_difference;
    Log(turn);

    Robot::m_DriveTrain->RawDrive(l + turn, r - turn);
  }

  // Reset the speed and rotation
  // while this does have some negitive side effects while driving,
  // It is for saftey. (and so we don't have a run-away bot slam into a wall again)
  this->speed    = 0.00;
  this->rotation = 0.00;
}


bool TriggerDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void TriggerDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TriggerDrive::Interrupted() {}
