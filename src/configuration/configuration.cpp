#include <libxml++/libxml++.h>

#include "configuration.h"
#include "../lib/logger.h"

Configuration::Configuration(const std::string& confFile) : m_confFile(confFile)
{
  
}

Configuration::~Configuration()
{

}

bool Configuration::loadConfiguration()
{
  xmlpp::DomParser parser;
  
  try {
    parser.parse_file(m_confFile);
  
    if(! parser)
    {
      err << "Cannot parse conf file " << m_confFile;
      return false;
    }
  } 
  catch (const std::exception& ex)
  {
    err << "Exception while loading configuration from file " << m_confFile;
    err << "Exception: " << ex.what();
    return false;
  }
  
  return true;
}
