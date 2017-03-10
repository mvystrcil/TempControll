#ifndef _H_CONFIGURATION
#define _H_CONFIGURATION

#include <string>
#include <libxml++/libxml++.h>
#include "../thermometer/thermometer.hpp"
#include "../thermometer/thermometerstatistics.h"

class Configuration
{
private:
  std::string m_confFile;
  const std::string XML_TAG_THERMOMETERS = "thermometers";
  const std::string XML_TAG_THERMOMETERS_PERIOD = "update-period";
  
  const std::string XML_TAG_THERMOMETER = "thermometer";
  const std::string XML_TAG_THERMOMETER_ADDRESS = "address";
  const std::string XML_TAG_THERMOMETER_MIN_TEMP = "minTemp";
  const std::string XML_TAG_THERMOMETER_MAX_TEMP = "maxTemp";
  
  bool loadThermometers(xmlpp::Node* node, ThermometerStatistics& statistics);
  bool loadThermometerSettings(xmlpp::Node *node, Thermometer *thermometer);
  
public:
  Configuration(const std::string& confFile);
  virtual ~Configuration();
  
  bool loadConfiguration(ThermometerStatistics& statistics);
};

#endif