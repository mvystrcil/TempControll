/*
 * ithermometer.hpp
 *
 *  Created on: 14. 2. 2017
 *      Author: martin
 */

#ifndef THERMOMETER_ITHERMOMETER_HPP_
#define THERMOMETER_ITHERMOMETER_HPP_

#include <string>

class IThermometer
{
public:
  explicit IThermometer(){};
  virtual ~IThermometer(){};

  virtual int getTemperature() const = 0;
  virtual std::string getThermometerName() const = 0;
};



#endif /* THERMOMETER_ITHERMOMETER_HPP_ */
