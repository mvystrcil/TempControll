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
  bool m_checkForExistence;

public:
  CreateTable(std::string tableName, bool checkForExistence = true);
  ~CreateTable();

  bool appendColumn(const SQLColumn& column);
  void checkIfExists(const bool checkForExistence);
  virtual std::string queryToString() const;
};

#endif
