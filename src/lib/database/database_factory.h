#ifndef _H_DATABASE_FACTORY
#define _H_DATABASE_FACTORY

#include "idatabase.h"
#include "sql.h"

#include <vector>
#include <unordered_map>

class DatabaseFactory
{

public:
  enum DatabaseTypes {SQLITE};
  ~DatabaseFactory();
  static DatabaseFactory& getInstance();
  bool loadSettings(const std::unordered_map<std::string, std::string>& settings, 
		    const bool closeAllPrev = false);

  IDatabase* getDatabase(const DatabaseFactory::DatabaseTypes& type);

private:
  IDatabase *instance;
  static bool configured;
  std::unordered_map<std::string, std::string> m_settings;
  DatabaseFactory();

};

#endif
