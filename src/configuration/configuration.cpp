#include "configuration.h"
#include "../lib/logger.h"

Configuration::Configuration(const std::string& confFile) : m_confFile(confFile)
{
  
}

Configuration::~Configuration()
{

}

bool Configuration::loadThermometers(xmlpp::Node *node)
{
  xmlpp::Node *child;
  xmlpp::Element *element;
  
  dbg << "Thermometers node: " << node->get_name();
  child = node->get_first_child();
  
  while(child)
  {
    if(child->get_name().compare(XML_TAG_THERMOMETER) == 0)
    {
      element = dynamic_cast<xmlpp::Element *>(child);
      dbg << "Elem " << child->get_name() << " id: " 
	<< element->get_attribute("id")->get_value()
	<< " name: "
	<< element->get_attribute("name")->get_value();
    }
    
    child = child->get_next_sibling();
  }
}

bool Configuration::loadConfiguration()
{
  xmlpp::DomParser parser;
  xmlpp::Node *pChildNode;
  xmlpp::Element *pRootElement;
  
  try {
    parser.parse_file(m_confFile);
  
    if(! parser)
    {
      err << "Cannot parse conf file " << m_confFile;
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
	this->loadThermometers(pChildNode);
      }
      
      pChildNode = pChildNode->get_next_sibling();
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
