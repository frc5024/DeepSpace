#include <Utils/AutoDrive.h>
#include <Robot.h>

void AutoDrive::Start(void)
{
	float a = 0.0 ; // Angle to target from the vision camera, relavent to the robot
	float d = 0.0 ; // Absolute distance to target from vision target

	float e = Robot::m_DriveTrain->GetAngle() ;
	float l = RADIAL_LENGTH ; // Length of robot

	float t ; // Target distance

	// Cosine law to calculate value of t
	t = std::sqrt( l*l + d*d - 2*l*d*std::cos(a) ) ;

	float h = std::asin( std::sin(a) * d / t) ;

	float g = 180 - h ;

	float i = e - g ;
	
	float f = 180 - i ;

	float theta = 180 - 2 * f ;

	float r = t * std::sin(f) / std::sin(theta) ;

	float w = RADIAL_WIDTH_WHEEL_2 ;

	float c1 = 2 * M_PI * (r + w) * (theta / 360) ;

	float m =  (r - w) / (r + w) ;

	float c0 = c1 * m ;


	

}

void AutoDrive::Execute(void)
{

	return ;
}

void AutoDrive::Stop(void)
{

	return ;
}

AutoDrive::AutoDrive(void)
{
    this->table = NetworkTable::GetTable("SmartDashboard/Vision") ;

}

bool AutoDrive::IsTurning(void)
{
    return this->turning ;
}
