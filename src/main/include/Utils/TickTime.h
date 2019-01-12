//! A simple timer that uses the robot period to track time
#ifndef _TICKTIME_HG_
#define _TICKTIME_HG_

class TickTime{
	public:
		TickTime();
		void Reset();        //!< Resets the ticker
		void Tick();         //!< Ticks the timer
		double GetSeconds(); //!< returns the number of seconds since the first tick
	private:
		int tick_count = 0;
}

#endif // _TICKTIME_HG_