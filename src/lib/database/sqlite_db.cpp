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

bool SQLiteDB::executeQuery(SQL *query)
{
  dbg << "Executing SQL query: " << query->queryToString() ;
}
