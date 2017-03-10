#ifndef _H_SUPERVISION
#define _H_SUPERVISION

#include "configuration/configuration.h"
#include "../thermometer/thermometerstatistics.h"

class Supervision
{
private:
  bool stop;
  std::string m_conf;
  ThermometerStatistics statistics;
  
  bool loadConfiguration();
public:
  Supervision();
  virtual ~Supervision();
  
  void setConfigurationFile(const std::string& conf);
  
  void init();
};

#endif