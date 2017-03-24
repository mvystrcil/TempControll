#include "createtable.h"

#include "logger.h"
#include <iterator>
#include <unordered_map>

CreateTable::CreateTable(std::string tableName, bool checkForExistence) : m_tableName(tableName), 
  m_checkForExistence(checkForExistence)
{
}

CreateTable::~CreateTable()
{

}

void CreateTable::checkIfExists(const bool checkForExistence)
{
  this->m_checkForExistence = checkForExistence;
}

bool CreateTable::appendColumn(const SQLColumn& column)
{
  m_tableColumns.push_back(column);
  
  return true;
}

std::string CreateTable::queryToString() const
{
  std::string query = "";
  std::string type;
  
  query.append("CREATE TABLE ").append(m_tableName);
  
  return query;
}
