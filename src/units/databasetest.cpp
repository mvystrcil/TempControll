#include "databasetest.h"
#include "../lib/logger.h"
#include "../lib/supervision.h"
#include "../lib/database/database_factory.h"

void DatabaseTest::setUp()
{
  databaseInstance = DatabaseFactory::getInstance().getDatabase(DatabaseFactory::DatabaseTypes::SQLITE);
}

void DatabaseTest::tearDown()
{

}

void DatabaseTest::createBasicTableTest()
{
  dbg << "Run basic DatabaseTest";
}
