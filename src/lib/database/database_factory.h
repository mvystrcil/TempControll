#ifndef _H_DATABASE_FACTORY
#define _H_DATABASE_FACTORY

#include "idatabase.h"

#include <vector>

class DatabaseFactory
{

public:
  enum DatabaseTypes {SQLITE};
  ~DatabaseFactory();
  static DatabaseFactory& getInstance();

  IDatabase* getDatabase(const DatabaseFactory::DatabaseTypes& type);

private:
  IDatabase *instance;
  DatabaseFactory();

};

#endif
