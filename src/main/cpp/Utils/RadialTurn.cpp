#include <Utils/AutoDrive.h>
#include <Robot.h>

using namespace std ; // Makes math look much cleaner

float RadialTurn::GetCruiseVelocity(float v, float distance)
{
	// Distance covered when deccelerating to 0 velocity from initial velocity
	float df = v * v / 2 * RADIAL_MAX_ACCEL ;

	// 
	/* Since accel = deccel,
	 * we can compensate for the initial velocity with the above distance
	 * divide by two get the one side of either accel or deccel, doesnt matter
	 */
	float d = (distance - df) / 2.0 ;

	/* Get the end velocity at the d distance covered.
	 * This will be the max velocity
	 */
	float v1 = sqrt( v*v + 2*RADIAL_MAX_ACCEL*d) ;

	/*
	
	(constant velocity)
	d2 = V * t + d1

	(exclude v2)
	d = 0.5 * a * t^2 + v1 * t

	(exclude v1)
	d = -0.5 * a * t^2 + v2 * t

	(exclude t)
	v2^2 = v1^2 + 2 * a * (d2 - d1)

	(exclude d)
	v2 = v1 + a * t

	(exclude a)
	d = 0.5 * (v2 - v1) * t

	*/

	return min32f(v1, RADIAL_MAX_VEL) ;
}

void RadialTurn::Start(void)
{
	/* * * * * * * * * * * * * * * * *
	 *        GIVEN VARIABLES        *
	 * * * * * * * * * * * * * * * * */
	float a = 0.0 ;						//!< Angle to target IN RADIANS from the vision camera, relavent to the robot
	float d = 0.0 ;						//!< Absolute distance to target from vision target
	float l = RADIAL_LENGTH ;			//!< Length of robot
	float w2 = RADIAL_WIDTH_WHEEL_2 ;	//!< Distance from left wheels to right wheels div 2
	float v1 = 0.0 ;					//!< Current velocity at the start of this command
	/* * * * * * * * * * * * * * * * */

	//!< Is the angle negative or positve, this way we can use absolute angle and then check against this later
	bool negative ;
	//!< Simple check of a
	if (a >= 0) {
		negative = false ;
	} else {
		negative = true ;
		a = -a ;
	}

	/* The target distance, t
	 * Centre-front of robot to target
	 * 
	 * Cosine law to calculate t using sides l, d, and angle a
	 */
	float t = sqrt( l*l + d*d - 2*l*d*cos(a) ) ;

	/* Symmetric angle of a triangle
	 * Used to grab theta and radius of our circle
	 * 
	 * Sin law of ?:d and a:t
	 * Then subtract 90deg as triangle is parrallel to front of robot
	 */
	float f = asin( sin(a) * d / t ) - M_PI_2 ;

	/* 
	 * Absolute angle we are turning
	 *  
	 * Simple angle subtraction to get theta
	 * as theta is apart of an isosceles triangle
	 */
	float theta = M_PI - 2 * f ;

	/*
	 * Set our delta angle we turning
	 * 
	 * Convert angle to degrees from radians
	 * and check to see if it's negative or not
	 */
	this->angleTurning = (negative)? -theta * 57.3 : theta * 57.3 ;

	/* Radius of the circle
	 * Is used to calculate our circumference, and therefore our path
	 * 
	 * Sin law ?:f & t:theta
	 */
	float r = t * sin(f) / sin(theta) ;	

	/*
	 * The outside path ( THE GREATER DISTANCE )
	 * 
	 * Is equal to 2*pi*r but r is + half the wheel base width
	 * and we multiply  
	 */
	float c1 = 2 * M_PI * (r + w2) * (theta / 2 / M_PI ) ;

	/* 
	 * Mutiplier to get the other circumference without re-calculating 2*pi*r*theta/c
	 * 
	 * It is infact "(2*pi*(r-w2)*theta/c) / (2*pi*(r+w2)*theta/c)"" except "2*pi*theta/c" cancel out
	 */
	float m = (r - w2) / (r + w2) ;

	//!< Apply the multiplier for the inside path (THE LESSER DISTANCE)
	float c0 = c1 * m ;

	/* 
	 * If turning left,
	 * the right wheels will have the longer path,
	 * the left wheels will have the shorter path.
	 * 
	 * If tuning right,
	 * the left wheels will have the longer path,
	 * the right wheels will have the short path.
	 */
	if (negative) {
		this->distancePathSideLeft = c0 ;
		this->distancePathSideRight = c1 ;
	} else {
		this->distancePathSideLeft = c1 ;
		this->distancePathSideRight = c0 ;
	}


	//TODO: Make trajectory constant for now, add em all to talon motion profile thing
	

}

void RadialTurn::Execute(void)
{
	
	return ;
}

void RadialTurn::Stop(void)
{

	return ;
}

RadialTurn::RadialTurn(void)
{
    this->table = NetworkTable::GetTable("SmartDashboard/Vision") ;

}

bool RadialTurn::IsTurning(void)
{
    return this->turning ;
}
