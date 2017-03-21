#ifndef _H_DATABASE
#define _H_DATABASE

#include "idatabase.h"

class SQLiteDB : public IDatabase
{
private:
  std::string m_databasePath;

public:
  SQLiteDB(const std::string &databasePath = "./temp_controll_db.sqlite3");
  ~SQLiteDB();

  bool openDatabase(std::vector<std::string> inputParams);
};


#endif
