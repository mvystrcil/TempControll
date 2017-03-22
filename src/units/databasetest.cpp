#include "databasetest.h"
#include "../lib/logger.h"
#include "../lib/supervision.h"
#include "../lib/database/database_factory.h"
#include "../lib/database/createtable.h"

void DatabaseTest::setUp()
{
  databaseInstance = DatabaseFactory::getInstance().getDatabase(DatabaseFactory::DatabaseTypes::SQLITE);
}

void DatabaseTest::tearDown()
{

}

void DatabaseTest::createBasicTableTest()
{
  CreateTable ctb("UniTestTable");
  ctb.appendColumn("Name", SQLTypes::STRING);
  
  CPPUNIT_ASSERT(databaseInstance->executeQuery(&ctb));
  dbg << "Run basic DatabaseTest";
  
}
