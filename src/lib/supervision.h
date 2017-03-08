#ifndef _H_SUPERVISION
#define _H_SUPERVISION

#include "thermometer/thermometerstatistics.h"
#include "thermometer/thermometerstatistics.h"
#include "thermometer/thermometerslist.h"

class Supervision
{
private:
  bool stop;
  void initThermometers();
  
  ThermometerStatistics stats;
  /*Thermometer th1;
  Thermometer th2;*/
  ThermometersList& list = ThermometersList::getInstance();
  
public:
  Supervision();
  virtual ~Supervision();  
  
  void init();
};

#endif