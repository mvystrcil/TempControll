#include "timerlib.h"
#include "../lib/logger.h"

TimerLib::TimerLib()
{

}

/*void TimerLib::addHandler(std::function<void(void)> callback)
{
	dbg << "Registered callback function " << lf;
	dbg << "Call this func immediatelly" << lf;
	callback();
}*/

bool TimerLib::registerHandler(TimeoutCallback callback, int timeout)
{
  dbg << "Register callback" << lf;
}

