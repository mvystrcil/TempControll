#ifndef UNITS_DATABASETEST_H_
#define UNITS_DATABASETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>

#include "../lib/logger.h"
#include "../lib/database/idatabase.h"
#include "../lib/database/database_factory.h"
#include "../lib/database/sqlite_db.h"

class DatabaseTest : public CppUnit::TestFixture
{
public:
  void setUp();
  void tearDown();

  static CppUnit::Test *suite()
  {
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("DatabaseTest cases");

    // Register all test functions
    
    /*suiteOfTests->addTest(new CppUnit::TestCaller<DatabaseTest>("Open table test",
				&DatabaseTest::openDatabaseTest));

    suiteOfTests->addTest(new CppUnit::TestCaller<DatabaseTest>("Double close table test",
				&DatabaseTest::doubleCloseTest));*/
    
    suiteOfTests->addTest(new CppUnit::TestCaller<DatabaseTest>("Create table test",
                                &DatabaseTest::createBasicTableTest));
    
    
    
    return suiteOfTests;
  }


protected:
  void openDatabaseTest();
  void doubleCloseTest();
  void createBasicTableTest();
  
private:
  const std::string sqlitePath = "./unit-test.sqlite3";
  const std::string sqliteDBPathParam = SQLiteDB::DATABASE_PATH_PARAM;
  const std::string sqlDatabaseName = "UnitTestTable";
  IDatabase *databaseInstance;
};

#endif
