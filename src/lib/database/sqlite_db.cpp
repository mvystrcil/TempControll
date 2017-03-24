#include "sqlite_db.h"

#include "logger.h"

SQLiteDB::SQLiteDB(const std::string& databasePath) : m_databasePath(databasePath)
{

}

SQLiteDB::~SQLiteDB()
{

}

bool SQLiteDB::openDatabase(std::vector<std::string> inputParams)
{
  dbg << "Open sqlite database";
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
