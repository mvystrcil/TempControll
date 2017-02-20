/*
 * thermometer.hpp
 *
 *  Created on: 14. 2. 2017
 *      Author: martin
 */

#ifndef THERMOMETER_THERMOMETER_HPP_
#define THERMOMETER_THERMOMETER_HPP_

#include <iostream>
#include <string>

#include "ithermometer.hpp"

using namespace std;

class Thermometer
{
public:
	/*
    Should I pass them by value, by (const) reference, or a pointer?

    	By const reference if object is big
    	by value if object is small
    	by const pointer if it is an optional argument that can be zero (i.e. "NULL")
    	by pointer if it is an optional argument that can be zero but will be owned (i.e. deallocated) by constructed class.
	 * */
	Thermometer(const string &name);
	~Thermometer();

	string getThermometerName() const;

    int getTemperature() const;
    bool updateTemperature(const int temperature);

    // Overload == operator to compare two instances
    bool operator==(const Thermometer &other) const;

private:
	string name;
	int temperature;
    int updatePeriod;

};

#endif /* THERMOMETER_THERMOMETER_HPP_ */
