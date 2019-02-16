/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef _MOVELEGSTO_HG_
#define _MOVELEGSTO_HG_

#include <frc/commands/TimedCommand.h>
#include <frc/DigitalInput.h>

class MoveLegsTo : public frc::TimedCommand {
public:

	/**
	 * @brief Position to move to
	 */
	enum Pos {
		P_TOP,
		P_MID,
		P_BOT
	} pos ;

	/**
	 * @brief Construct a new Move Legs To object
	 * @param position Enum position to move to
	 * @param spd Speed percent of motor output to move at
	 * @param timeout Time seconds to wait until timeout
	 */
	explicit MoveLegsTo(Pos position, double spd, double timeout);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	
	/**
	 * @brief Speed to maintain
	 */
	double spd ;

} ;

#endif /* _MOVELEGSTO_HG_ */
