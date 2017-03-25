#include "sqlite_db.h"

#include "logger.h"

const std::string SQLiteDB::DATABASE_PATH_PARAM  = "DATABASE_PATH";

SQLiteDB::SQLiteDB(const std::string& databasePath) : m_databasePath(databasePath)
{

}

SQLiteDB::~SQLiteDB()
{

}

bool SQLiteDB::openDatabase(const std::unordered_map< std::string, std::string >& params)
{
  auto findIterator = params.find(DATABASE_PATH_PARAM);
  
  dbg << "File: " << findIterator->first;
  
  return true;
}


/*
 * Distinguish based on type of SQL query and serialize the request
 * accodingly to its syntax
 */
bool SQLiteDB::executeQuery(SQL *query)
{
  dbg << "Executing SQL query: " << query->queryToString();
  
  return true;
}
