#ifndef _H_SQL_COLUMN
#define _H_SQL_COLUMN

#include "sql_types.h"

#include <string>

class SQLColumn
{

public:
  SQLColumn(std::string columnName, SQLTypes::ColumnType type);
  ~SQLColumn();

  std::string getColumnName() const;
  SQLTypes::ColumnType getColumnType() const;
  
private:
  std::string m_columnName;
  SQLTypes::ColumnType m_columnType;

};

#endif
