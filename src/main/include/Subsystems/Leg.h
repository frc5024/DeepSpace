#ifndef _LEG_HG_
#define _LEG_HG_

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "RobotMap.h"

class Leg : public frc::Subsystem {
  public:
    Leg();
    void InitDefaultCommand() override;
  
    /**
  	 * Move climb leg up or down
  	 *
  	 * @param Speed speed (from -1 to 1)
  	 */
    void MoveLeg(double Speed);
  private:
    can::WPI_TalonSRX* pLegMotor; //!< Pointer for Climb Leg Motor
};

#endif // _LEG_HG_