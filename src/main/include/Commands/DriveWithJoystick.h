//! An interface command for driving the robot with an xbox controller
#ifndef _DRIVEWITHJOYSTICK_HG_
#define _DRIVEWITHJOYSTICK_HG_

#include <Commands/Command.h>
#include <Subsystems/DriveTrain.h>

class DriveWithJoystick : public frc::Command {
 public:
  DriveWithJoystick();        //!< Class constructor
  void Initialize() override; //!< Runs once on initalization
  void Execute() override;    //!< Called in a loop during Teleop
  
  /**
   * Used to tell wpilib if the command is fully finished. This should never return true
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

/**
 * driveMode is set depending on what is selected from drivermenu
 *
 * 0 = Joystick
 * 1 = Triggers
 */
int driveMode = 0;

frc::XboxController* pJoyDrive; //!< A mnemonic for the driver's controller because we are lazy
};

#endif // _DRIVEWITHJOYSTICK_HG_