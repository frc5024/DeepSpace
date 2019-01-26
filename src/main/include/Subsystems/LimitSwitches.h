//#pragma once
#ifndef _LIMITSWITCHES_HG_
#define _LIMITSWITCHES_HG_

#include <frc/DigitalInput.h>
#include <frc/commands/Subsystem.h>

class LimitSwitches : public frc::Subsystem {
 public:
  LimitSwitches();
  void InitDefaultCommand() override;
  
  // Todo: rename these variables to more accurate names for the limit switches used on the robot.
  // mabye rename to getValue() because unknown if ls's are normally open or closed
  bool isOn1(); //!<
  bool isOn2(); //!<
  int ChannelNumber();

 private:
  frc::DigitalInput* limitSwitch1; //!< The first limit switch on the robot
  frc::DigitalInput* limitSwitch2; //!< The second limit switch on the robot
};

#endif // _LIMITSWITCHES_HG_