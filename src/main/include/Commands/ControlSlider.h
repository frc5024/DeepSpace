//! An interface command for driving the robot with an xbox controller
#ifndef _ControlSlider_HG_
#define _ControlSlider_HG_

#include <frc/commands/Command.h>
#include <Subsystems/Slider.h>
#include "RobotMap.h"
#include <frc/GenericHID.h>


class ControlSlider : public frc::Command {
 public:
  ControlSlider();             //!< Class constructor
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
	double speed;    //!< Speed value that will be passed into Slider::Slide
	
	frc::XboxController* pJoyOp; //!< A mnemonic for the driver's controller because we are lazy
};

#endif // _ControlSlider_HG_