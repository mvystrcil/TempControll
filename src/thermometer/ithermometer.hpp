/*
 * ithermometer.hpp
 *
 *  Created on: 14. 2. 2017
 *      Author: martin
 */

#ifndef THERMOMETER_ITHERMOMETER_HPP_
#define THERMOMETER_ITHERMOMETER_HPP_

#include <string>

using namespace std;

class IThermometer
{
	IThermometer();
	virtual ~IThermometer();

	int getActualTemperature();
	string getThermometerName();
};



#endif /* THERMOMETER_ITHERMOMETER_HPP_ */
