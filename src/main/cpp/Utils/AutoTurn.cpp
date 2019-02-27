#include <Utils/AutoTurn.h>
#include <Robot.h>

AutoTurn::AutoTurn(void) {
    
    // Init stored variable to 0
    this->offset    = 0.0 ;
    this->target    = 0.0 ;
    this->turning   = false ;
    this->integral  = 0.0 ;
    
	this->offsetID = -1 ;

    // Init the Vision net table
    this->table = NetworkTable::GetTable("SmartDashboard/Vision") ;

    return ;
}

void AutoTurn::Start(void) {
    
	// Set an angle offset to effectively zero our yaw
	this->offsetID = Robot::m_ConstGyro->CreateAngleGetter();

	// Set this target to the angle to target
	this->target = this->table->GetNumber("Motor", 0.0) ;

	// Log it
	std::cout << "Starting AutoTurn with angle: ("<<this->target<<").\n" ;

	// Turning is now active
	this->turning = true ;

	return ;
}

void AutoTurn::Stop(void) {

	// Set all variables to 0
	this->turning = false ;
	this->offset = 0.0 ;
	this->target = 0.0 ;
	this->integral = 0.0 ;

	Robot::m_ConstGyro->DeleteAngleGetter(this->offsetID);
	this->offsetID = -1;
	
	// This didn't break it before though it should
	Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0) ;

	return ;
}

double AutoTurn::Execute(void) {
	
	if (this->turning == false) {
		return 0.0 ;
	}

	// Get current angle, relevent to where we started
	float current = Robot::m_ConstGyro->GetAngle(this->offsetID);

	// Get error, degrees remaining to target
	float error = this->target - current ;

	// Check if we've reached our target
	if (fabs(error) <= PID_BUFFER) {
		this->Stop() ;
		return 0.0 ;
	}

	// Increment the integral, this is why it's important to conistantly call this function
	this->integral += error * ROBOT_CYCLE_TIME ;

	// Calculate the PID output!
	// PID = P * error + I * integral + D * derivative
	double PIDOutput = PID_TWEAK_P * error + PID_TWEAK_I * this->integral ;

	// Log it (TEMPORARY)
	std::cout<<"PID: "<<PIDOutput<<" = "<<PID_TWEAK_P<<" * "<<error<<" + "<<PID_TWEAK_I<<" * "<<this->integral<<std::endl;
	// (TEMPORARY)

	return PIDOutput ;
}

bool AutoTurn::IsTurning(void) {
	return this->turning ;
}
