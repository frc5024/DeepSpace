//! A subsystem that interfaces with the drivebase on the robot
#ifndef _Slider_HG_
#define _Slider_HG_

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <frc/Encoder.h>
#include <ctre/Phoenix.h>
#include "RobotMap.h"
#include <Commands/ControlSlider.h>

class Slider : public frc::Subsystem {
 public:
  Slider(); //!< Class constructor
  void InitDefaultCommand() override; //!< Initalizes the default command for this subsystem (ControlSlider)
	
	/**
	 * Pass data to motor
	 *
	 * @param speed Slider speed (form -1 to 1)
	 */
  	void Slide(double speed);

  	/**
	 * @brief Resets all encoder sensor positions to 0
	 */
	void ResetEncoders(void);

	/**
	 * @brief Resets the left side encoder sensor positions to 0
	 */
	void ResetLeftEncoder(void);

	/**
	 * @brief Resets the right side encoder sensor positions to 0
	 */
	void ResetRightEncoder(void);

	/**
	 * @brief Get's the average of all encoder values in cm
	 * @return Distance delta in centimetres
	 */
	float GetDistance(void);

	/**
	 * @brief Gets the distance of ONLY the FRONT RIGHT motor
	 * @remark Only uses FRONT RIGHT motor
	 * @remark Equivalent to GetRightDistanceQuick(void)
	 * @return Distance delta in centimetres
	 */
	float GetDistanceQuick(void);

	/**
	 * @brief Get's the average of all left side encoder values in cm
	 * @return Distance delta in centimetres
	 */
	float GetLeftDistance(void);

	/**
	 * @brief Get's the average of all right side encoder values in cm
	 * @return Distance delta in centimetres
	 */
	float GetRightDistance(void);

	/**
	 * @brief Gets the distance of ONLY the FONT LEFT motor
	 * @remark Only uses the FRONT LEFT motor
	 * @return Distance delta in centimetres
	 */
	float GetLeftDistanceQuick(void);

	/**
	 * @brief Gets the distance of ONLY the FONT RIGHT motor
	 * @remark Only uses the FRONT RIGHT motor
	 * @remark Equivalent to GetDistanceQuick(void)
	 * @return Distance delta in centimetres
	 */
	float GetRightDistanceQuick(void);

 private:
  can::WPI_TalonSRX* pSliderMotor; //!< Pointer for the slider motor
};

#endif // _Slider_HG_