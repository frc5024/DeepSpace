//! A subsystem that controls the climbing of the robot
#ifndef _CLIMB_HG_
#define _CLIMB_HG_

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <frc/AnalogInput.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include "RobotMap.h"

class Climb : public frc::Subsystem {
 public:
  Climb();
  void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (Climb)

  /**
	 * Move climb arm up or down
	 *
	 * @param Speed speed (from -1 to 1)
	 */
  void MoveArm(double Speed);

  /**
	 * Move climb leg up or down
	 *
	 * @param Speed speed (from -1 to 1)
	 */
  void MoveLeg(double Speed);

  /**
	 * returns distance from floor
	 *
	 */
  double getDistanceFromFloor();


  private:
  can::WPI_TalonSRX* pArmMotor; //!< Pointer for climb arm motor
  can::WPI_TalonSRX* pLegMotor; //!< Pointer for climb leg motor
  frc::AnalogInput m_ultrasonic{CLIMB_ULTRASONIC};
  static constexpr double kValueToInches = 0.125;
};

#endif // _CLIMB_HG_