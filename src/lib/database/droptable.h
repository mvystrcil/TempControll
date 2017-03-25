#ifndef _H_DROP_TABLE
#define _H_DROP_TABLE

#include "sql.h"
#include "sql_column.h"

#include <vector>

class DropTable : public SQL
{

private:
  std::string m_tableName;

public:
  DropTable(std::string tableName);
  ~DropTable();
  
  virtual std::string queryToString() const;
};

#endif