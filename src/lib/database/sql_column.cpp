#include "sql_column.h"

/*SQLColumn::SQLColumn(std::string columnName, SQLTypes::ColumnType type) : m_columnName(columnName), m_columnType(type)
{

}*/

SQLColumn::SQLColumn(std::string columnName, SQLTypes::ColumnType type, bool id, bool autoInc, bool notNull) :
  m_columnName(columnName), m_columnType(type), m_id(id), m_autoInc(autoInc), m_notNull(notNull)
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

bool SQLColumn::getAutoIncrement() const
{
  return this->m_autoInc;
}

bool SQLColumn::getID() const
{
  return this->m_id;
}

bool SQLColumn::getNotNullValue() const
{
  return this->m_notNull;
}
