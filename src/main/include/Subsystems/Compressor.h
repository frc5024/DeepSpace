//! A subsystem that interfaces with the robot's compressor
#ifndef _COMPRESSOR_HG_
#define _COMPRESSOR_HG_

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"
#include <Commands/ControlCompressor.h>
#include <frc/Compressor.h>

class Compressor : public frc::Subsystem {
 public:
  Compressor(); //!< Class constructor
  void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (DriveWithJoystick)
	
	/**
	 * Pass data to Compressor
	 *
	 * @param enabled Bool to determine if the compressor should be enabled or not
	 */
  void SetState(bool enabled);

 private:
  frc::Compressor* pCompressor;
};

#endif // _COMPRESSOR_HG_