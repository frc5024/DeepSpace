#include "Utils/AutoTurn.h"
#include "Robot.h"

float AutoTurn::target = 0.0 ;
float AutoTurn::integral = 0.0 ;
AHRS* AutoTurn::pGyro = new AHRS(SPI::Port::kMXP);
std::shared_ptr<NetworkTable> AutoTurn::table = NetworkTable::GetTable("SmartDashboard/Vision");

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

	// Calculate values (current angle, degrees difference to target, integral of error)
	float current = AutoTurn::pGyro->GetAngle() ;
	float err = AutoTurn::target - current ;
	AutoTurn::integral += err * CYCLE_TIME;

	// If we're within X degrees of target, stop
	if (fabs(err) < PID_BUFFER) {
		AutoTurn::Stop() ;
		return 0.0;
	}

	double PIDOutput = PID_TWEAK_P * err + PID_TWEAK_I * AutoTurn::integral;
	/*TEMP*/std::cout<<"PID: "<<PIDOutput<<" = "<<PID_TWEAK_P<<" * "<<err<<" + "<<PID_TWEAK_I<<" * "<<AutoTurn::integral<<std::endl;/*TEMP*/
	
	return PIDOutput;
}
