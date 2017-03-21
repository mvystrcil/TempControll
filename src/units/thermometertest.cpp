/*
 * ThermometerTest.cpp
 *
 *  Created on: 14. 2. 2017
 *      Author: martin
 */

#include "thermometertest.h"
#include <string>

void ThermometerTest::setUp()
{
  thermometerA = new Thermometer("A");
  thermometerB = new Thermometer("B");
}

void ThermometerTest::tearDown()
{
  // Thermometerlist delete all instances by itself now
  /*delete(thermometerA);
  delete(thermometerB);*/
}

void ThermometerTest::createThermometerObjects()
{
  CPPUNIT_ASSERT(thermometerA != NULL);
  CPPUNIT_ASSERT(thermometerB != NULL);

  CPPUNIT_ASSERT((thermometerA == thermometerB) == false);
  CPPUNIT_ASSERT((thermometerA == thermometerA) == true);
  CPPUNIT_ASSERT((thermometerB == thermometerB) == true);
}

void ThermometerTest::checkThermometerObjects()
{
	string thermometerName;

	thermometerName = thermometerA->getThermometerName();
	CPPUNIT_ASSERT(thermometerName.compare("A") == 0);

	thermometerName = thermometerB->getThermometerName();
	CPPUNIT_ASSERT(thermometerName.compare("B") == 0);
}

void ThermometerTest::registerThermometers()
{
    Thermometer test("test");

    //ThermometersList& list2 = ThermometersList::getInstance();
    // Compare if these two instanaces are the same
    //CPPUNIT_ASSERT(list == list2);

    CPPUNIT_ASSERT(ThermometersList::getInstance().registerThermometer(thermometerA) == true);
    CPPUNIT_ASSERT(ThermometersList::getInstance().registerThermometer(thermometerB) == true);
    CPPUNIT_ASSERT(ThermometersList::getInstance().registerThermometer(thermometerA) == false);

    CPPUNIT_ASSERT(ThermometersList::getInstance().unregisterThermometer(&test) == false);
    CPPUNIT_ASSERT(ThermometersList::getInstance().unregisterThermometer(thermometerA) == true);
    CPPUNIT_ASSERT(ThermometersList::getInstance().unregisterThermometer(thermometerA) == false);
    CPPUNIT_ASSERT(ThermometersList::getInstance().unregisterThermometer(thermometerB) == true);
    CPPUNIT_ASSERT(ThermometersList::getInstance().unregisterThermometer(thermometerB) == false);
    CPPUNIT_ASSERT(ThermometersList::getInstance().unregisterThermometer(&test) == false);
}
