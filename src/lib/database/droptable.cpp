#include "droptable.h"

DropTable::DropTable(std::string tableName) : m_tableName(tableName)
{

}

DropTable::~DropTable()
{

}

std::string DropTable::queryToString() const
{
  std::string query;
  
  query.append("DROP TABLE").append(" ");
  query.append(m_tableName);
  
  return query;
}