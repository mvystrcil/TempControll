#ifndef _H_SUPERVISION
#define _H_SUPERVISION

#include "configuration/configuration.h"
#include "../thermometer/thermometerstatistics.h"

class Supervision
{
private:
  bool stop;
  std::string m_conf;
  const int SUPERVISE_PERIOD_CHECK_MS = 100;
  ThermometerStatistics statistics;
  
  bool loadConfiguration();
  bool supervise();
public:
  Supervision();
  virtual ~Supervision();
  
  void setConfigurationFile(const std::string& conf);
  
  void init();
};

#endif