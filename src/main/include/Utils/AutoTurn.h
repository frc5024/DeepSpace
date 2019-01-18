//! Util class for
#ifndef _AUTOTURN_HG_
#define _AUTOTURN_HG_

#include <iostream>
#include <RobotMap.h>
#include <AHRS.h>
#include <frc/Timer.h>
#include <networktables/NetworkTable.h>

class AutoTurn{
  public:
    AutoTurn(); //!< Class constructor
    
    /**
     * Function for setting the target angle
     *
     * @param angle Angle to rotate to
     */
    void SetAngle(float angle);
  
  private:
    float target;                        //!< Target angle
    AHRS* m_pGryo;                       //!< Pointer to the navX
  	frc::Timer* m_pTimer;                //!< Timer for tracking time
  	std::shared_ptr<NetworkTable> table; //!< A pointer to the /SmartDashboard/Vision table
}

#endif // _AUTOTURN_HG_