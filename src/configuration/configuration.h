#ifndef _H_CONFIGURATION
#define _H_CONFIGURATION

#include <string>
#include <libxml++/libxml++.h>

class Configuration
{
private:
  std::string m_confFile;
  const std::string XML_TAG_THERMOMETERS = "thermometers";
  const std::string XML_TAG_THERMOMETER = "thermometer";
  
  bool loadThermometers(xmlpp::Node *node);
  
public:
  Configuration(const std::string& confFile);
  virtual ~Configuration();
  
  
  bool loadConfiguration();
};

#endif