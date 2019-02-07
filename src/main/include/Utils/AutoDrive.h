/**
 * @file AutoDrive.h
 * @author RaiderRobotics.com
 * @brief Utility class for automatically driving to the grabbed vision target
 * This Object will grab from network tables for the vision target
 * Then calculate a circle to path to the bay perpindicular
 * Then form a trajectory curve along that circle
 * Then follow it until robot reaches target
 * 
 *  ==== HOW TO USE ====
 * 1. Call Start() to grab the vision target distance and angle, program will subsequently calculate the required path
 * 2. Run Execute() as long as it is still turning, program will do PIDF to follow along
 * 3. Run Stop() whenever you want, or let the object call Stop() itself when it reaches the target
 * =====================
 * @version 1.0
 * @date 2019-02-06
 */

#ifndef _AUTODRIVE_HG_
#define _AUTODRIVE_HG_

#include <NetworkTable.h>

class AutoDrive
{
public:
    /**
     * @brief TODO: documentation
     * 
     */
    void Start(void) ;

    /**
     * @brief TODO: documentation
     * 
     */
    void Execute(void) ;

    /**
     * @brief TODO: documentation
     * 
     */
    void Stop(void) ;

private:


};

#endif /* _AUTODRIVE_HG_ */
