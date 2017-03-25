#include "databasetest.h"
#include "../lib/logger.h"
#include "../lib/supervision.h"
#include "../lib/database/database_factory.h"
#include "../lib/database/createtable.h"
#include "../lib/database/droptable.h"
#include "../lib/database/sql_column.h"

#include <unordered_map>

void DatabaseTest::setUp()
{
  databaseInstance = DatabaseFactory::getInstance().getDatabase(DatabaseFactory::DatabaseTypes::SQLITE);
}

void DatabaseTest::tearDown()
{

  
  databaseInstance->closeDatabase();
}

void DatabaseTest::openDatabaseTest()
{
  std::unordered_map<std::string, std::string> params;
  
  // Test opening database without settings
  CPPUNIT_ASSERT(! (databaseInstance->openDatabase(params)));
  
  // Now open with parameters set
  params.insert({sqliteDBPathParam, sqlitePath});
  CPPUNIT_ASSERT(databaseInstance->openDatabase(params));
}

void DatabaseTest::doubleCloseTest()
{
  std::unordered_map<std::string, std::string> params;
  params.insert({sqliteDBPathParam, sqlitePath});
  
  dbg << "Try to close database which is not opened";
  CPPUNIT_ASSERT(databaseInstance->closeDatabase());
  
  databaseInstance->openDatabase(params);
  dbg << "Close database which is opened";
  CPPUNIT_ASSERT(databaseInstance->closeDatabase());
  
  dbg << "Close the database again";
  CPPUNIT_ASSERT(databaseInstance->closeDatabase());
}

void DatabaseTest::createBasicTableTest()
{
  std::unordered_map<std::string, std::string> params;
  CreateTable ctb(sqlDatabaseName);
  DropTable dtbl(sqlDatabaseName);
  
  params.insert({sqliteDBPathParam, sqlitePath});
  CPPUNIT_ASSERT(databaseInstance->openDatabase(params));
  
  // Fill in some data to database  
  ctb.appendColumn(SQLColumn("ID", SQLTypes::INT, true, true, true));
  ctb.appendColumn(SQLColumn("Name", SQLTypes::STRING));
  ctb.appendColumn(SQLColumn("Address", SQLTypes::STRING));
  
  CPPUNIT_ASSERT(databaseInstance->executeQuery(ctb));
  dbg << "Run basic DatabaseTest";  
  
  // Clear database
  databaseInstance->executeQuery(dtbl);
}