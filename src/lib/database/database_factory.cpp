#include "database_factory.h"

#include "../logger.h"
#include "sqlite_db.h"

DatabaseFactory::DatabaseFactory()
{

}

/*
 * Delete all instances which we allocated
*/
DatabaseFactory::~DatabaseFactory()
{

}

IDatabase* DatabaseFactory::getDatabase(const DatabaseFactory::DatabaseTypes& type)
{
  switch(type)
  {
    case DatabaseTypes::SQLITE:
      dbg << "Create database of SQLite type";
      if(instance == nullptr)
      {
        instance = new SQLiteDB();
      }
      return instance;
    break;

    default:
      errn << "Unknown database type: " << type;
    break;
  }

  return nullptr;
}



