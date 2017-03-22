#ifndef UNITS_DATABASETEST_H_
#define UNITS_DATABASETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include <chrono>

class DatabaseTest : public CppUnit::TestFixture
{
public:
  void setUp();
  void tearDown();

  static CppUnit::Test *suite()
  {
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("DatabaseTest cases");

    // Register all test functions

    suiteOfTests->addTest(new CppUnit::TestCaller<DatabaseTest>("Create table test",
                                &DatabaseTest::createBasicTableTest));

  }


protected:
  void createBasicTableTest();
};

#endif
