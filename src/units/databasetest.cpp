#include "databasetest.h"
#include "../lib/logger.h"
#include "../lib/supervision.h"
#include "../lib/database/database_factory.h"
#include "../lib/database/createtable.h"
#include "../lib/database/sql_column.h"

void DatabaseTest::setUp()
{
  databaseInstance = DatabaseFactory::getInstance().getDatabase(DatabaseFactory::DatabaseTypes::SQLITE);
}

void DatabaseTest::tearDown()
{

}

void DatabaseTest::createBasicTableTest()
{
  CreateTable ctb("UnitTestTable");
  ctb.appendColumn(SQLColumn("ID", SQLTypes::INT, true, true, true));
  ctb.appendColumn(SQLColumn("Name", SQLTypes::STRING));
  ctb.appendColumn(SQLColumn("Address", SQLTypes::STRING));
  
  CPPUNIT_ASSERT(databaseInstance->executeQuery(&ctb));
  dbg << "Run basic DatabaseTest";
  
}
