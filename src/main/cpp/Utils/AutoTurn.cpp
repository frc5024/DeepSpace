#include "Utils/AutoTurn.h"
#include "Robot.h"

AutoTurn::target = 0.0 ;
AutoTurn::pGryo = new AHRS(SPI::Port::kMXP);
AutoTurn::table = NetworkTable::GetTable("SmartDashboard/Vision");

void AutoTurn::SetTarget(float angle) {

	///< Brings the angle within (-180, 180) deg 
    while (true) {
		if (angle > 180.0)		angle -= 360.0;
		elif (angle < -180.0)	angle += 360.0;
		else					break;
	} 

	AutoTurn::target = angle ;
	std::cout << "Set target to ("<<angle<<")\n" ;

	return ;
}

void AutoTurn::GetData(void) {
	AutoTurn::pGyro->Reset() ;
	float angle = AutoTurn::table->GetNumber("Motor", 0.0);
	AutoTurn::SetTarget(angle) ;

	return ;
}

void AutoTurn::Stop(void) {
	Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0) ;
	AutoTurn::target = 0.0 ;
	AutoTurn::integral = 0.0 ;
	AutoTurn::pGyro->Reset() ;

	return ;
}

double AutoTurn::Turn(void) {
	float current = AutoTurn::pGyro->GetAngle() ;
	float err = AutoTurn::target - current ;

	// If we're within X degrees of target, stop
	if (fabs(err) < PID_BUFFER) {
		AutoTurn::Stop() ;
		return 0.0;
	}

	if (err > 0.0) {
		std::cout << "Turning right...\n" ;
		return 0.5 ;
	} else {
		std::cout << "Turning left...\n" ;
		return -0.5 ;
	}
	return 0.0;
}
