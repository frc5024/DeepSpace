#ifndef _CONTROLSLIDER_HG_
#define _CONTROLSLIDER_HG_

#include <frc/commands/Command.h>
#include <Subsystems/Slider.h>
#include "RobotMap.h"
#include <frc/GenericHID.h>

/**
 *
 */
class ControlSlider : public frc::Command 
{
public:
  ControlSlider(); 
  void Initialize() override;
  void Execute() override; 
  bool IsFinished() override;
  void End() override; 
  void Interrupted() override;
  
private:
  frc::XboxController* pJoystickOperator; 
  double speed; 
};

#endif 
