#include "sqlite_db.h"
//#include "consts/databases.h"

SQLiteDB::SQLiteDB(const std::string& databasePath) : m_databasePath(databasePath)
{
  database = nullptr;
}

SQLiteDB::~SQLiteDB()
{

}

bool SQLiteDB::openDatabase(const std::unordered_map< std::string, std::string >& params)
{
  int rc = 0;
  std::string file;
  auto findIterator = params.find("DATABASE_PATH");
  
  if(findIterator != params.end())
  {
    file = findIterator->second;
    dbg << "Open database file: " << file;
    
    rc = sqlite3_open(file.c_str(), &database);
    if(rc)      
    {
      warn << "Cannot open file " << findIterator->second << " rc: " << rc;
      sqlite3_close(database);
      return false;
    }
    
    return true;
  }
  
  warn << "Cannot find attribute " << "DATABASE_PATH" << ", DB not opened";
  return false;
}

bool SQLiteDB::closeDatabase()
{
  int rc = 0;
  
  if(database == nullptr)
  {
    // Already closed or even not opened yet
    return true;
  }
  
  rc = sqlite3_close(database);
  if(rc != SQLITE_OK)
  {
    errn << "Error while closing database";
    errn << "RC: " << rc;
    
    return false;
  }
  
  database = nullptr;  
  return true;
}

/*bool SQLiteDB::clearDatabase()
{
  if(database == nullptr)
  {
    // database not opened, so cannot delete it
    return false;
  }
  
  database->getFile();
}*/

/*
 * Distinguish based on type of SQL query and serialize the request
 * accodingly to its syntax
 */
bool SQLiteDB::executeQuery(const SQL& query)
{
  int rc = 0;
  char *err;
  
  dbg << "Start with execute query";
  
  if(! isDatabaseOpen())
  {
    errn << "Database is not opened - cannot execute query";
    return false;
  }
  
  dbg << "Executing SQL query: " << query.queryToString();
  
  rc = sqlite3_exec(database, query.queryToString().c_str(), callback, 0, &err);
  
  if(rc != SQLITE_OK)
  {
    warn << "Cannot execute query: " << query.queryToString();
    warn << "RC code: " << rc;
    
    sqlite3_free(err);
    return false;
  }
  
  return true;
}

bool SQLiteDB::isDatabaseOpen()
{  
  return (database == nullptr ? false : true);
}
