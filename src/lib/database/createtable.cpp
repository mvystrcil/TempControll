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
  bool column = false;
  std::vector<SQLColumn> copy = m_tableColumns;
  std::vector<SQLColumn>::iterator iterator = copy.begin();  
  
  // Maybe could be user some prepared statements ...
  query.append("CREATE TABLE ").append(m_tableName).append("(");
  
  while(iterator != copy.end())
  {
    SQLColumn col = (SQLColumn) *iterator;
    
    if(column)
    {
      query.append(",");
    }
    
    query.append(col.getColumnName()).append(" ");
    query.append(SQLTypes::getColumnType(col.getColumnType())).append(" ");
    
    if(col.getID())
    {
      query.append("PRIMARY KEY").append(" ");
    }
    
    if(col.getNotNullValue())
    {
      query.append("NOT NULL").append(" ");
    }
    
    column = true;
    iterator++;
  }
  
  query.append(");");
  return query;
}
