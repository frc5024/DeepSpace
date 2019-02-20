#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
#include <string>
#include <fstream>

// Subsystems
DriveTrain *Robot::m_DriveTrain;
Compressor *Robot::m_Compressor;
CrawlDrive *Robot::m_CrawlDrive;
Arm *Robot::m_Arm;
Leg *Robot::m_Leg;
OI *Robot::m_oi;
Slider *Robot::m_Slider;
Piston *Robot::m_Piston;

void Robot::RobotInit() {
	// Print out a banner to the shell
	// Some backslashes are doubled in order for them to print properly
	std::cout << "   Welcome 5024!" << std::endl;
	std::cout << "-------------------" << std::endl;
	std::cout << "Robot Starting.."<< std::endl;

	// Subsystems
	std::cout << "Creating Subsystems..." << std::endl;
	this->m_DriveTrain = new DriveTrain();
	this->m_CrawlDrive = new CrawlDrive();
	this->m_Arm        = new Arm();
	this->m_Leg        = new Leg();
	this->m_Slider     = new Slider();
	this->m_Piston     = new Piston();
	this->m_oi         = new OI();
	this->m_Compressor = new Compressor();

	// Init camera
	std::cout << "Starting CameraServer.." << std::endl;
	this->frontCam  = frc::CameraServer::GetInstance()->StartAutomaticCapture("Driver Camera", CAMERASERVER_DRIVER_CAMERA);
	this->visionCam = frc::CameraServer::GetInstance()->StartAutomaticCapture("Vision",  CAMERASERVER_VISION_CAMERA);

	// Set vision cam settings
	std::cout << "Setting camera config.." << std::endl;
	std::ifstream visionSettingsFile("/home/lvuser/deploy/vision_camera_settings.json");
	std::string visionSettings((std::istreambuf_iterator<char>(visionSettingsFile)), (std::istreambuf_iterator<char>()));
	this->visionCam.SetConfigJson(visionSettings);

	// Init commands
	std::cout << "Creating Commands.." << std::endl;
	this->pTriggerDrive = new TriggerDrive();
	this->pTestUltra = new testUltra();
	this->pPullArm = new PullArm();
	this->pPullLeg = new PullLeg();
	this->pAutoHighClimb = new AutoHighClimb();
	this->pControlSlider = new ControlSlider();
	this->pControlCompressor = new ControlCompressor();
	this->pClimbManager = new ClimbManager();
	
	// Create Telemetry table
	std::cout << "Connecting to telemetry table.." << std::endl;
	this->ntTelemetry = NetworkTable::GetTable("SmartDashboard/Telemetry");

	// create ds and pdp objects
	std::cout << "Creating Driverstation and PDP objects" << std::endl;
	this->pdp = new frc::PowerDistributionPanel(10);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
	// Send information about the robot over NetworkTables

	double pdpTemperature = this->pdp->GetTemperature();
	double robotVoltage   = this->pdp->GetVoltage();
	bool   dsAttached     = this->driverStation.IsDSAttached();
	bool   fmsAttached    = this->driverStation.IsFMSAttached();

	this->ntTelemetry->PutNumber("pdp_temp", pdpTemperature);
	this->ntTelemetry->PutNumber("voltage",  robotVoltage);
	this->ntTelemetry->PutBoolean("DSconn",  dsAttached);
	this->ntTelemetry->PutBoolean("FMSconn", fmsAttached);

	if(frc::RobotController::GetUserButton()){
		this->m_Leg->MoveLeg(1.0) ;
	}
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {frc::Scheduler::GetInstance()->Run();}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {
	std::cout << "Initting auto!\n" ;

	if (this->pAutoHighClimb != nullptr) {
		std::cout << "Starting pLowerArm!\n" ;
		this->pAutoHighClimb->Start() ;
	} else {
		std::cout << "LowerArm was null!\n";
	}

	// std::string autoSelected = frc::SmartDashboard::GetString(
	//     "Auto Selector", "Default");
	// if (autoSelected == "My Auto") {
	//   m_autonomousCommand = &m_myAuto;
	// } else {
	//   m_autonomousCommand = &m_defaultAuto;
	// }

	// m_autonomousCommand = m_chooser.GetSelected();

	// if (m_autonomousCommand != nullptr) {
	//   m_autonomousCommand->Start();
	// }
}

void Robot::AutonomousPeriodic() {frc::Scheduler::GetInstance()->Run();}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	// if (m_autonomousCommand != nullptr) {
	//   m_autonomousCommand->Cancel();
	//   m_autonomousCommand = nullptr;
	// }

	if (this->pTriggerDrive != nullptr) {
		this->pTriggerDrive->Start();
	}
	//   if (this->pTestUltra != nullptr) {
	// 		this->pTestUltra->Start();
	// 	}
	if (this->pPullArm != nullptr) {
		this->pPullArm->Start();
	}
	if (this->pPullLeg != nullptr) {
		this->pPullLeg->Start();
	}
	if (this->pControlSlider != nullptr) {
		this->pControlSlider->Start();
	}
	if (this->pControlCompressor != nullptr) {
		this->pControlCompressor->Start();
	}
	if (this->pClimbManager != nullptr) {
		this->pClimbManager->Start();
	}
}

void Robot::TeleopPeriodic()
{
	switch (ClimbManager::CurrentClimbState)
	{
		case ClimbManager::kInactive :
			if (this->pTriggerDrive != nullptr && !this->pTriggerDrive->IsRunning()) // Restart TriggerDrive once climb is done
				this->pTriggerDrive->Start();
			break;
		case ClimbManager::kSemiAuto :
			break;
		case ClimbManager::kAuto :
			if (this->pAutoHighClimb != nullptr && !this->pAutoHighClimb->IsRunning()) // Enable command group on kAuto
				this->pAutoHighClimb->Start();
		default:
			break;
	}

	frc::Scheduler::GetInstance()->Run(); 
}

void Robot::TestPeriodic() {}


#ifndef RUNNING_FRC_TESTS
int main(){
	// Start the robot
	WinGame(Robot);
	return 1;
}
#endif
