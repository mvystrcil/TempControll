#ifndef _H_DATABASE
#define _H_DATABASE

#include "idatabase.h"

#include <string>

class SQLiteDB : public IDatabase
{

public:
  SQLiteDB(const std::string &databasePath = "./temp_controll_db.sqlite3");
  ~SQLiteDB();

  bool openDatabase(std::vector<std::string> inputParams);

private:
  std::string m_databasePath;
};


#endif
