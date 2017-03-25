#ifndef _H_DATABASE
#define _H_DATABASE

#include "idatabase.h"
#include "logger.h"
#include "../../external/sqlite/sqlite3.h"

#include <string>
#include <unordered_map>

class SQLiteDB : public IDatabase
{
private:
  sqlite3 *database;
  
public:
  static const std::string DATABASE_PATH_PARAM;
  
  SQLiteDB(const std::string &databasePath = "./temp_controll_db.sqlite3");
  ~SQLiteDB();

  bool openDatabase(const std::unordered_map<std::string, std::string>& params);
  bool closeDatabase();
  bool executeQuery(SQL *query);

private:
  std::string m_databasePath;
  
  static int callback(void* NotUsed, int argc, char** argv, char** azColName)
  {
    int i;
    for(i=0; i<argc; i++){
      errn << ("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
    }
    return 0; 
  }
};


#endif
