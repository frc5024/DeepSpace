#include <Utils/AutoDrive.h>
#include <Robot.h>

void Start(void)
{
	float a = 0.0 ; // Angle to target from the vision camera, relavent to the robot
	float d = 0.0 ; // Absolute distance to target from vision target

	float l = ROBOT_LENGTH ; // Length of robot

	float t ; // Target distance

	// Cosine law to calculate value of t
	t = std::sqrt( l*l + d*d - 2*l*d*math.cos(a) ) ;

	float e ;

}

void Execute(void)
{

}

void Stop(void)
{

}

AutoDrive(void)
{
    

}

bool IsTurning(void)
{
    return this->turning ;
}
