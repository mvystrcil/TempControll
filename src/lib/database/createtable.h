#ifndef _H_CREATE_TABLE
#define _H_CREATE_TABLE

#include "sql.h"
#include "sql_column.h"

#include <vector>

class CreateTable : public SQL
{

private:
  std::string m_tableName;
  std::vector<SQLColumn> m_tableColumns;

public:
  CreateTable(std::string tableName);
  ~CreateTable();

  bool appendColumn(std::string columnName, SQLTypes::ColumnType columnType);
};

#endif
