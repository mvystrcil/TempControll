#ifndef _H_CONFIGURATION
#define _H_CONFIGURATION

#include <string>

class Configuration
{
private:
  std::string m_confFile;
  
public:
  Configuration(const std::string& confFile);
  virtual ~Configuration();
  
  
  bool loadConfiguration();
};

#endif