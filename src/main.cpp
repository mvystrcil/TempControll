#include <iostream>

#include "thermometer/thermometerstatistics.h"
#include "thermometer/thermometerslist.h"
#include "thermometer/thermometerstatistics.h"

using namespace std;

#ifndef _UNIT_TESTS
#define _UNIT_TESTS
int main(int argc, char* argv[])
{
    ThermometersList *list;
    ThermometerStatistics stats;
    Thermometer th1("AA");
    Thermometer th2("BB");

	cout << "Starting program to collect all incoming data" << endl;
    list = ThermometersList::getInstance();

    list->registerThermometer(th1);
    list->registerThermometer(th2);

    stats.startStatsColl();

	return 0;	
}
#endif
