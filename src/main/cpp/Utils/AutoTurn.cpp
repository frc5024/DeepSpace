#include "Utils/AutoTurn.h"
#include "Robot.h"

std::shared_ptr<NetworkTable> AUTOTURN_table = NetworkTable::GetTable("SmartDashboard/Vision"); //!< A pointer to the /SmartDashboard/Vision table
AHRS* AUTOTURN_m_pGryo = new AHRS(SPI::Port::kMXP); //!< Pointer to the navX
frc::Timer* AUTOTURN_m_pTimer = new frc::Timer();   //!< Timer for tracking time
float AUTOTURN_target;

void AUTOTURN_SetTarget(float angle){
    while (true) {
		if (angle > 180.0)		angle -= 360.0;
		elif (angle < -180.0)	angle += 360.0;
		else					break;
	} 
	AUTOTURN_target = angle ;
	std::cout << "Set target to ("<<AUTOTURN_target<<")\n" ;

	return ;
  
}

void AUTOTURN_GetData(){
    AUTOTURN_m_pTimer->Reset() ;
	AUTOTURN_m_pGryo->Reset() ;

	float angle = AUTOTURN_table->GetNumber("Motor", 0.0);
	AUTOTURN_SetTarget(angle) ;

	AUTOTURN_m_pTimer->Start() ;

	return ;

}

void AUTOTURN_Stop() {
	Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0) ;
	AUTOTURN_target = 0.0 ;
	AUTOTURN_m_pGryo->Reset() ;
	AUTOTURN_m_pTimer->Reset() ;
	AUTOTURN_m_pTimer->Stop() ;

	return ;
}

double AUTOTURN_Turn() {
	float current = AUTOTURN_m_pGryo->GetAngle() ;
	float err = AUTOTURN_target - current ;

	if (fabs(err) < 1) {
		AUTOTURN_Stop() ;
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
