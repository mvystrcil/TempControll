#include "sqlite_db.h"

const std::string SQLiteDB::DATABASE_PATH_PARAM  = "DATABASE_PATH";

SQLiteDB::SQLiteDB(const std::string& databasePath) : m_databasePath(databasePath)
{

}

SQLiteDB::~SQLiteDB()
{

}

bool SQLiteDB::openDatabase(const std::unordered_map< std::string, std::string >& params)
{
  int rc = 0;
  std::string file;
  auto findIterator = params.find(DATABASE_PATH_PARAM);
  
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
  
  warn << "Cannot find attribute " << DATABASE_PATH_PARAM << ", DB not opened";
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


/*
 * Distinguish based on type of SQL query and serialize the request
 * accodingly to its syntax
 */
bool SQLiteDB::executeQuery(SQL *query)
{
  int rc = 0;
  char *err;
  
  dbg << "Executing SQL query: " << query->queryToString();
  
  rc = sqlite3_exec(database, query->queryToString().c_str(), callback, 0, &err);
  
  if(rc != SQLITE_OK)
  {
    warn << "Cannot execute query: " << query->queryToString();
    warn << "RC code: " << rc;
    
    sqlite3_free(err);
    return false;
  }
  
  return true;
}