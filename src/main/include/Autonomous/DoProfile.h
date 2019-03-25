#ifndef _AUTONOMOUS_DOPROFILE_H
#define _AUTONOMOUS_DOPROFILE_H

#include <frc/commands/TimedCommand.h>
#include <Subsystems/DriveTrain.h>

class DoProfile : public frc::TimedCommand {
 public:
  explicit DoProfile(double timeout, TankProfile *profile);
  void Initialize() override;
  void Execute() override;
  void End() override;
  void Interrupted() override;
 private:
   TankProfile *profile;
};

#endif //_AUTONOMOUS_DOPROFILE_H