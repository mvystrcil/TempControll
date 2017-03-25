#ifndef _H_DATABASE
#define _H_DATABASE

#include "idatabase.h"

#include <string>
#include <unordered_map>

class SQLiteDB : public IDatabase
{

public:
  static const std::string DATABASE_PATH_PARAM;
  
  SQLiteDB(const std::string &databasePath = "./temp_controll_db.sqlite3");
  ~SQLiteDB();

  bool openDatabase(const std::unordered_map<std::string, std::string>& params);
  
  bool executeQuery(SQL *query);

private:
  std::string m_databasePath;
};


#endif
