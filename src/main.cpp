#include "lib/logger.h"
#include "thermometer/thermometerstatistics.h"
#include "thermometer/thermometerslist.h"
#include "thermometer/thermometerstatistics.h"
#include "lib/timerlib.h"

#include <string>

#ifndef _UNIT_TESTS
Logger dbg("logger.log", true);
std::string lf = "\n";

int main(int argc, char* argv[])
{
    ThermometerStatistics stats;
    Thermometer th1("AA");
    Thermometer th2("BB");

	dbg << "Starting program to collect all incoming data" << lf;
	ThermometersList& list = ThermometersList::getInstance();

    list.registerThermometer(th1);
    list.registerThermometer(th2);

    stats.startStatsColl();
    
    return 0;	
}
#endif
