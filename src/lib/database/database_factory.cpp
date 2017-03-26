#include "database_factory.h"

#include "../logger.h"
#include "sqlite_db.h"

bool DatabaseFactory::configured;

DatabaseFactory::DatabaseFactory()
{
  configured = false;
}

/*
 * Delete all instances which we allocated
*/
DatabaseFactory::~DatabaseFactory()
{
  if(instance != nullptr)
  {
    instance->closeDatabase();
    delete(instance);
    instance = nullptr;
  }
}

DatabaseFactory& DatabaseFactory::getInstance()
{
  static DatabaseFactory instance;
  return instance;
}

bool DatabaseFactory::loadSettings(const std::unordered_map< std::string, std::string >& settings, 
				   const bool closeAllPrev)
{
  if(configured && closeAllPrev)
  {
    dbg << "Reload settings and close all current connections";
    
    if(instance != nullptr)
    {
      instance->closeDatabase();
      delete(instance);
    }
  }
  else if(configured)
  {
    warn << "Trying to configure factory which is already configured";
    return false;
  }
  
  m_settings = settings;
  configured = true;
  return true;
}

IDatabase* DatabaseFactory::getDatabase(const DatabaseFactory::DatabaseTypes& type)
{
  
  if(!configured)
  {
    warn << "Still no configuration loaded, load some at first";
    return nullptr;
  }
  
  switch(type)
  {
    case DatabaseTypes::SQLITE:
      dbg << "Create database of SQLite type";
      
      if(instance == nullptr)
      {
        instance = new SQLiteDB();
	if(! instance->openDatabase(m_settings))
	{ 
	  warn << "Cannot open database, please check";
	  delete(instance);
	  instance = nullptr;
	  
	  return nullptr;
	}
      }
      
      return instance;
    break;

    default:
      errn << "Unknown database type: " << type;
    break;
  }

  return nullptr;
}



