#ifndef _HALLEFFECT_HG_
#define _HALLEFFECT_HG_

#include <frc/DigitalInput.h>
#include <frc/commands/Subsystem.h>

class HallEffect : public frc::Subsystem {
 public:
  HallEffect();
  void InitDefaultCommand() override;
 
  // todo: rename variable's below (yes, I know I'm bad at naming):
  bool nearMagnet1(); //!< Gets and returns a true or false statement if a magnet is near the first hall sensor
  bool nearMagnet2(); //!< Gets and returns a true or false statement if a magnet is near the second hall sensor

 private:
  frc::DigitalInput* hallSensor1; //!< The first hall effect sensor on the robot
  frc::DigitalInput* hallSensor2; //!< The second hall effect sensor on the robot
  // TODO: Add more hall effect sensors to the subsystem here... Also probably rename variables.
};

#endif // _HALLEFFECT_HG_