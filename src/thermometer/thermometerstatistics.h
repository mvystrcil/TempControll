#ifndef THERMOMETERSTATISTICS_H
#define THERMOMETERSTATISTICS_H

#include "../lib/timerlib.h"
#include "thermometer/ithermometer.hpp"

class ThermometerStatistics
{
public:
  ThermometerStatistics(int updateTimeout=defaultTimeout);
  virtual ~ThermometerStatistics();
  
  int getUpdateTimeout() const;
  bool setUpdateTimeout(const int timeout);
  
  bool startStatsColl();
  bool stopStatsColl() const;

private:
  static const int defaultTimeout = 30000;
  int updateTimeout;
  TimerLib *timer = nullptr;
  
  void updateAllThermometers();
  bool storeThermometerData(const IThermometer* thermometer);
};

#endif // THERMOMETERSTATISTICS_H
