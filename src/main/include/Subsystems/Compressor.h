//! A subsystem that interfaces with the robot's cCompressor
#ifndef _cCompressor_HG_
#define _cCompressor_HG_

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
#include <Commands/ControlCompressor.h>
#include <frc/Compressor.h>

class cCompressor : public frc::Subsystem {
 public:
  cCompressor(); //!< Class constructor
  void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (DriveWithJoystick)
	
	/**
	 * Pass data to cCompressor
	 *
	 * @param enabled Bool to determine if the cCompressor should be enabled or not
	 */
  void SetState(bool enabled);

 private:
  frc::Compressor* pCompressor;
};

#endif // _cCompressor_HG_