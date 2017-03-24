#ifndef _H_SQL_COLUMN
#define _H_SQL_COLUMN

#include "sql_types.h"

#include <string>

class SQLColumn
{

public:
  SQLColumn(std::string columnName, SQLTypes::ColumnType type, 
	    bool id = false, bool autoInc = false, bool notNull = true);
  ~SQLColumn();

  std::string getColumnName() const;
  SQLTypes::ColumnType getColumnType() const;
  bool getNotNullValue() const;
  bool getID() const;
  bool getAutoIncrement() const;
  
private:
  std::string m_columnName;
  bool m_notNull, m_id, m_autoInc;
  
  SQLTypes::ColumnType m_columnType;

};

#endif
