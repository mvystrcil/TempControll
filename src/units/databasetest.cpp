#include "databasetest.h"
#include "../lib/logger.h"
#include "../lib/supervision.h"
#include "../lib/database/database_factory.h"
#include "../lib/database/createtable.h"
#include "../lib/database/sql_column.h"
#include "../lib/database/sqlite_db.h"

#include <unordered_map>

void DatabaseTest::setUp()
{
  databaseInstance = DatabaseFactory::getInstance().getDatabase(DatabaseFactory::DatabaseTypes::SQLITE);
}

void DatabaseTest::tearDown()
{

}

void DatabaseTest::createBasicTableTest()
{
  std::unordered_map<std::string, std::string> params;
  const std::string path = "./unit-test.sqlite3";
  const std::string db = SQLiteDB::DATABASE_PATH_PARAM;
  
  CPPUNIT_ASSERT(! (databaseInstance->openDatabase(params)));
  
  // Now open with parameters set
  params.insert({db, path});
  CPPUNIT_ASSERT(databaseInstance->openDatabase(params));
  
  CreateTable ctb("UnitTestTable");
  ctb.appendColumn(SQLColumn("ID", SQLTypes::INT, true, true, true));
  ctb.appendColumn(SQLColumn("Name", SQLTypes::STRING));
  ctb.appendColumn(SQLColumn("Address", SQLTypes::STRING));
  
  CPPUNIT_ASSERT(databaseInstance->executeQuery(&ctb));
  dbg << "Run basic DatabaseTest";
  
}
