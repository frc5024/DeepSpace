//! Util class for
#ifndef _AUTOTURN_HG_
#define _AUTOTURN_HG_

#include <iostream>
#include <RobotMap.h>
#include <AHRS.h>
#include <frc/Timer.h>
#include <networktables/NetworkTable.h>



  extern void AUTOTURN_GetData() ;
  extern double AUTOTURN_Turn() ;


  /**
   * Function for setting the target angle
   *
   * @param angle Angle to rotate to
   */
  extern void AUTOTURN_SetTarget(float angle);
  extern void AUTOTURN_Stop() ;


  extern float AUTOTURN_target;                        //!< Target angle


#endif // _AUTOTURN_HG_