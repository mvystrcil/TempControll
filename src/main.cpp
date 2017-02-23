#include "lib/logger.h"
#include "thermometer/thermometerstatistics.h"
#include "thermometer/thermometerslist.h"
#include "thermometer/thermometerstatistics.h"
#include "lib/supervision.h"
#include "lib/timerlib.h"

#include <string>
#include <thread>

#ifndef _UNIT_TESTS
Logger dbg("logger.log", true);
std::string lf = "\n";

int main(int argc, char* argv[])
{
    Supervision supervision;
    
    std::thread main(&Supervision::init, &supervision);
    main.join();
    dbg << "Exiting" << lf;
    
    return 0;	
}
#endif
