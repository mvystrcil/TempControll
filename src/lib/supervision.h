#ifndef _H_SUPERVISION
#define _H_SUPERVISION

#include "configuration/configuration.h"

class Supervision
{
private:
  bool stop;
  std::string m_conf;
  
  bool loadConfiguration();
public:
  Supervision();
  virtual ~Supervision();
  
  void setConfigurationFile(const std::string& conf);
  
  void init();
};

#endif