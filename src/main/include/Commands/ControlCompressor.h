//! An interface command for driving the robot with an xbox controller
#ifndef _CONTROLCOMPRESSOR_HG_
#define _CONTROLCOMPRESSOR_HG_

#include <frc/commands/Command.h>
#include <Subsystems/Compressor.h>
#include "RobotMap.h"
#include <frc/GenericHID.h>
#include <frc/WPILib.h>


class ControlCompressor : public frc::Command {
 public:
  ControlCompressor();             //!< Class constructor
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
	frc::XboxController* pJoyOp;    //!< A mnemonic for the operator's controller
  frc::XboxController* pJoyDrive; //!< A mnemonic for the driver's controller
};

#endif // _CONTROLCOMPRESSOR_HG_