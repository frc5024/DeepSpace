//! An interface command for driving the robot with an xbox controller
#ifndef _TRIGGERDRIVE_HG_
#define _TRIGGERDRIVE_HG_

#include <frc/commands/Command.h>
#include <Subsystems/DriveTrain.h>
#include "RobotMap.h"
#include <frc/GenericHID.h>

#include <pathfinder.h>
#include <AHRS.h>


class TriggerDrive : public frc::Command {
 public:
  TriggerDrive();             //!< Class constructor
  void Initialize() override; //!< Runs once on initalization
  void Execute() override;    //!< Called in a loop during Teleop
  
  /**
   * Used to tell wpilib if the command is fully finished. This should never return true
   * Because we always want to be able to drive the bot during teleop
   *
   * @return True if command is finished, else false
   */
  bool IsFinished() override;
  
  void End() override;         //!< Runs once when IsFinished() returns true
  void Interrupted() override; //!< Runs once if the command is forced to stop
  
private:
	int directionMultiplier; //!< Can be 1 or -1. Determines the direction the the robot moves in
	double speedMultiplier;  //!< The speed of the robot is multiplied by this number. Used for slowmode
	
	double speed;    //!< Speed value that will be passed into DriveTrain::ArcadeDrive
	double rotation; //!< Rotation value that will be passed into DriveTrain::ArcadeDrive
	
	frc::XboxController* pJoyDrive; //!< A mnemonic for the driver's controller because we are lazy

  
  Segment trajectory[1024];     // Over allocate as we don't know the length yet
  int legnth = 13;
  double wheelbase_width = 0.5017;

  Segment leftTrajectory[13];
  Segment rightTrajectory[13];
  EncoderFollower followerL;
  // = new EncoderFollower;
  EncoderFollower followerR;
  // = new EncoderFollower;
  // followerL->last_error = 0; followerL->segment = 0; followerL->finished = 0;
  // followerR.last_error = 0; followerR.segment = 0; followerR.finished = 0;

  EncoderConfig configL;
  EncoderConfig configR;

  AHRS *pGyro;
};

#endif // _TRIGGERDRIVE_HG_