#include <Utils/AutoTurn.h>
#include <Robot.h>

AutoTurn::AutoTurn(void) {
    
    // Init stored variable to 0
    this->offset    = 0.0 ;
    this->target    = 0.0 ;
    this->turning   = false ;
    this->integral  = 0.0 ;
    
    // Create the gyro
    this->pGyro = new AHRS(SPI::Port::kMXP) ;

    // Init the Vision net table
    this->table = NetworkTable::GetTable("SmartDashboard/Vision") ;

    return ;
}

void AutoTurn::Start(void) {
    
	// Let Zero where the the robot is looking without resetting the gyro
	this->offset = this->pGyro->GetAngle() ;

	// Get the angle to target
	float angle = this->table->GetNumber("Motor", 0.0) ;
	
	// Set this target to the angle to target
	this->target = angle ;

	// Log it
	std::cout << "Starting AutoTurn with angle: ("<<angle<<").\n" ;

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
	
	// This didn't break it before though it should
	Robot::m_DriveTrain->ArcadeDrive(0.0, 0.0) ;

	return ;
}

double AutoTurn::Execute(void) {
	
	if (this->turning == false) {
		return 0.0 ;
	}

	// Get current angle, relevent to where we started
	float current = this->pGyro->GetAngle() - this->offset ;

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
