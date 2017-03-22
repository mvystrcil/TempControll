#include "sql_column.h"

SQLColumn::SQLColumn(std::string columnName, SQLTypes::ColumnType type) : m_columnName(columnName), m_columnType(type)
{

}

SQLColumn::~SQLColumn()
{

}

std::string SQLColumn::getColumnName() const
{
  return this->m_columnName;
}

SQLTypes::ColumnType SQLColumn::getColumnType() const
{
  return this->m_columnType;
}



