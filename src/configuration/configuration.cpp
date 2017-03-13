#include "configuration.h"
#include "../lib/logger.h"
#include "../thermometer/thermometerslist.h"

Configuration::Configuration(const std::string& confFile) : m_confFile(confFile)
{
  
}

Configuration::~Configuration()
{

}

bool Configuration::loadThermometers(xmlpp::Node *node, ThermometerStatistics& statistics)
{
  xmlpp::Node *child;
  xmlpp::Element *element;
  xmlpp::ContentNode *content;
  xmlpp::TextNode *text;
  
  Thermometer *thermometer;
  ThermometersList list = ThermometersList::getInstance();
  
  dbg << "Thermometers node: " << node->get_name();
  child = node->get_first_child();
  
  while(child)
  {
    element = dynamic_cast<xmlpp::Element *>(child);
    
    if(child->get_name().compare(XML_TAG_THERMOMETER) == 0)
    {
      // Get attributes of thermometer
      thermometer = new Thermometer(element->get_attribute_value("name"),
				    element->get_attribute_value("address"));
      
      // Read also settings of this thermometer
      this->loadThermometerSettings(child, thermometer);
      
      // Register thermometer to the list of known
      list.registerThermometer(thermometer);
    }
    else if (child->get_name().compare(XML_TAG_THERMOMETERS_PERIOD) == 0)
    {
      dbg << "Update timeout: " << element->get_child_text()->get_content();
      statistics.setUpdateTimeout(atoi(element->get_child_text()->get_content().c_str()));
    }
    
    child = child->get_next_sibling();
  }
}

bool Configuration::loadThermometerSettings(xmlpp::Node* node, Thermometer *thermometer)
{
  xmlpp::Node *child;
  xmlpp::Element *element;
  double minTemp;
  double maxTemp;
  std::string address;
  
  child = node->get_first_child();
  
  while(child)
  {
    element = dynamic_cast<xmlpp::Element *>(child);
    
    if(child->get_name().compare(XML_TAG_THERMOMETER_ADDRESS) == 0)
    {
      address = element->get_child_text()->get_content();
    }
    else if(child->get_name().compare(XML_TAG_THERMOMETER_MIN_TEMP) == 0)
    {
      minTemp = atof(element->get_child_text()->get_content().c_str());
    }
    else if(child->get_name().compare(XML_TAG_THERMOMETER_MAX_TEMP) == 0)
    {
      maxTemp = atof(element->get_child_text()->get_content().c_str());
    }
    
    child = child->get_next_sibling();
  }
  
  thermometer->setAddress(address);
  thermometer->setMinMaxTemp(minTemp, maxTemp);
}

bool Configuration::loadConfiguration(ThermometerStatistics& statistics)
{
  xmlpp::DomParser parser;
  xmlpp::Node *pChildNode;
  xmlpp::Element *pRootElement;
  
  try {
    parser.parse_file(m_confFile);
  
    if(! parser)
    {
      errn << "Cannot parse conf file " << m_confFile;
      return false;
    }
    
    pRootElement = parser.get_document()->get_root_node();
    
    dbg << "Root Element " << pRootElement->get_name();    
    if(pRootElement->get_name().compare("TemperatureController") != 0)
    {
      warn << "First tag in configuration file does not match 'TemperatureController', skip load conf";
      warn << "First tag: " << pRootElement->get_name();
      return false;
    }
    
    pChildNode = pRootElement->get_first_child();
    
    while(pChildNode)
    {
      
      if(pChildNode->get_name().compare(XML_TAG_THERMOMETERS) == 0)
      {
	this->loadThermometers(pChildNode, statistics);
      }
      
      pChildNode = pChildNode->get_next_sibling();
    }
    
  } 
  catch (const std::exception& ex)
  {
    errn << "Exception while loading configuration from file " << m_confFile;
    errn << "Exception: " << ex.what();
    return false;
  }
  
  return true;
}

