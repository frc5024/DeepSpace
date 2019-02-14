//! An interface command for activating the Pull Arm on the robot
#ifndef _Crawl_HG_
#define _Crawl_HG_

#include <frc/commands/TimedCommand.h>
#include <Subsystems/Arm.h>

class Crawl : public frc::TimedCommand {
 public:
  explicit Crawl(double speed, double timeout);
  void Initialize() override;
  void Execute() override;
  void End() override;
  void Interrupted() override;
 private:
  double speed;
};

#endif // _Crawl_HG_