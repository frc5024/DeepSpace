#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
#include <string>
#include <fstream>

#include "Utils/EdgeLight.h"

// /home/lvuser/FRC_UserProgram.log

// Subsystems
DriveTrain   *Robot::m_DriveTrain;
cCompressor  *Robot::m_cCompressor;
CrawlDrive   *Robot::m_CrawlDrive;
Arm          *Robot::m_Arm;
Leg          *Robot::m_Leg;
OI           *Robot::m_oi;
Slider       *Robot::m_Slider;
Piston       *Robot::m_Piston;
HatchGripper *Robot::m_HatchGripper;
Flap         *Robot::m_Flap;
Light        *Robot::m_Light;

void Robot::RobotInit() {
  // Print out a banner to the shell
  std::cout << "   Welcome 5024!"    << std::endl;
  std::cout << "-------------------" << std::endl;
  std::cout << "Robot Starting.."    << std::endl;

  // Subsystems
  Header("Creating Subsystems.. ");
  this->m_DriveTrain   = new DriveTrain();
  this->m_CrawlDrive   = new CrawlDrive();
  this->m_Arm          = new Arm();
  this->m_Leg          = new Leg();
  this->m_Slider       = new Slider();
  this->m_Piston       = new Piston();
  this->m_oi           = new OI();
  this->m_cCompressor  = new cCompressor();
  this->m_HatchGripper = new HatchGripper();
  this->m_Flap         = new Flap();
  this->m_Light        = new Light();
  EndHeader();

  // Init commands
  Header("Creating Commands.. ");
  this->pTriggerDrive        = new TriggerDrive();
  this->pJoystickTankDrive   = new JoystickTankDrive();
  this->pPullArm             = new PullArm();
  this->pPullLeg             = new PullLeg();
  this->pControlSlider       = new ControlSlider();
  this->pControlCompressor   = new ControlCompressor();
  this->pControlHatchGripper = new ControlHatchGripper();
  this->pControlCargo        = new ControlCargo();
  this->pControlLight        = new ControlLight();
  this->pClimbManager        = new ClimbManager();
  this->pAutoClimbHigh       = new AutoClimbHigh();
  this->pClimb               = new Climb();
  EndHeader();

  // Init camera
  Header("Starting CameraServer.. ");
  this->frontCam  = frc::CameraServer::GetInstance()->StartAutomaticCapture("Back",  CAMERASERVER_DRIVER_CAMERA);
  this->visionCam = frc::CameraServer::GetInstance()->StartAutomaticCapture("Front", CAMERASERVER_VISION_CAMERA);
  EndHeader();

  // Set vision cam settings
  Header("Setting camera config.. ");
  std::ifstream visionSettingsFile("/home/lvuser/deploy/config.json");
  std::string visionSettings((std::istreambuf_iterator<char>(visionSettingsFile)), (std::istreambuf_iterator<char>()));
  this->visionCam.SetConfigJson(visionSettings);
  this->frontCam.SetConfigJson(visionSettings);
  EndHeader();

  // Init Gyro
  Header("Resetting Gyro.. ");
  this->pGyro = new AHRS(frc::SPI::kMXP);
  this->pGyro->Reset();
  EndHeader();

  // Create Telemetry table
  Header("Connecting to telemetry table.. ");
  this->ntTelemetry = NetworkTable::GetTable("SmartDashboard/Telemetry");
  EndHeader();

  // create ds and pdp objects
  // std::cout << "Creating Driverstation and PDP objects" << std::endl;
  // this->pdp = new frc::PowerDistributionPanel(10);
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

  bool   dsAttached     = this->driverStation.IsDSAttached();
  bool   fmsAttached    = this->driverStation.IsFMSAttached();
  float  gyroAngle      = this->pGyro->GetAngle();

  this->ntTelemetry->PutBoolean("DSconn",  dsAttached);
  this->ntTelemetry->PutBoolean("FMSconn", fmsAttached);
  this->ntTelemetry->PutNumber("Angle", gyroAngle);
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {
  Header("Robot disabling.. ");
  Robot::m_Flap->Release();

  // Stop controller vibration once match ends
  if(this->pClimbManager != nullptr){
    this->pClimbManager->pJoyOp->SetRumble(frc::GenericHID::RumbleType::kRightRumble, 0.0);
  }
  EndHeader();
}

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
  Header("AutonomousInit starting.. ");
  this->SharedInit();
  EndHeader();

  Header("Resetting gyro.. ");
  this->pGyro->Reset();
  EndHeader();
}

void Robot::AutonomousPeriodic() { 
  this->SharedPeriodic();
  frc::Scheduler::GetInstance()->Run();
  Utils::EdgeLight::Push();
}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  // if (m_autonomousCommand != nullptr) {
  //   m_autonomousCommand->Cancel();
  //   m_autonomousCommand = nullptr;
  // }
  Header("Teleop commands starting.. ");
  this->SharedInit();
  EndHeader();
}

void Robot::TeleopPeriodic() { 
  this->SharedPeriodic();
  frc::Scheduler::GetInstance()->Run();
  Utils::EdgeLight::Push();
}

void Robot::SharedInit(){
    if (this->pTriggerDrive        != nullptr) { this->pTriggerDrive->Start();        }
    if (this->pPullArm             != nullptr) { this->pPullArm->Start();             }
    if (this->pPullLeg             != nullptr) { this->pPullLeg->Start();             }
    if (this->pControlSlider       != nullptr) { this->pControlSlider->Start();	    }
    if (this->pControlCompressor   != nullptr) { this->pControlCompressor->Start();	}
    if (this->pControlHatchGripper != nullptr) { this->pControlHatchGripper->Start();   }
    if (this->pControlCargo        != nullptr) { this->pControlCargo->Start();          }
    if (this->pControlLight        != nullptr) { this->pControlLight->Start();        }
    if (this->pClimbManager        != nullptr) { this->pClimbManager->Start();        }

    std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
    for (char c : gameData) c = std::tolower(c) ; // Make it all lowercase
    Log("gameData = " << gameData)
    if (gameData == "tank") {
        if (this->pJoystickTankDrive != nullptr) {
            this->pJoystickTankDrive->Start() ;
        }
    } else {
        if (this->pTriggerDrive != nullptr) {
            this->pTriggerDrive->Start();
        }
    }
}

void Robot::SharedPeriodic(){

    // Active certain commands if we want to start climbing
    switch (ClimbManager::CurrentClimbState) {
        case ClimbManager::ClimbState::kInactive: 
            this->pClimbManager->UpdateRumble();
            break;
        case ClimbManager::ClimbState::kActive:
            if (this->pClimb != nullptr) {
                this->pClimb->Start(); // Start manual climb commands
                this->pClimbManager->UpdateRumble(); // rumble controller
            }
            break;
        case ClimbManager::ClimbState::kAuto:
            if ( ! this->pAutoClimbHigh->IsClimbing())
                if (this->pAutoClimbHigh != nullptr) {
                    this->pAutoClimbHigh->Start(); // Start auto climb command
                    this->pClimbManager->UpdateRumble(); // rumble controller
                }
            break;
        default:
            Log("ClimbManager's climb state was invalid, setting to Inactive");
            ClimbManager::CurrentClimbState = ClimbManager::ClimbState::kInactive;
            break;
    }

  if(this->driverStation.GetAlliance() == frc::DriverStation::Alliance::kBlue){
    if(this->driverStation.IsOperatorControl()){
      Utils::EdgeLight::Append(LedColour::kCHASE_BLUE);
    }else{
      Utils::EdgeLight::Append(LedColour::kBEAT_BLUE);
    }
    
  }else if(this->driverStation.GetAlliance() == frc::DriverStation::Alliance::kRed){
    if(this->driverStation.IsOperatorControl()){
      Utils::EdgeLight::Append(LedColour::kCHASE_RED);
    }else{
      Utils::EdgeLight::Append(LedColour::kBEAT_RED);
    }

  }else{
    Utils::EdgeLight::Append(LedColour::kSOLID_WHITE);
  }
}

void Robot::TestPeriodic() {}


#ifndef RUNNING_FRC_TESTS
int main(){
  // Start the robot
  WinGame(Robot);
  Log("FATAL!!! Robot program finished!!!");
  return 1;
}
#endif
