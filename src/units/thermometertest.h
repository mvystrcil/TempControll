/*
 * ThermometerTest.h
 *
 *  Created on: 14. 2. 2017
 *      Author: martin
 */

#ifndef UNITS_THERMOMETERTEST_H_
#define UNITS_THERMOMETERTEST_H_

#include <iostream>
#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>

#include "../thermometer/thermometer.hpp"
#include "../thermometer/thermometerslist.h"

class ThermometerTest : public CppUnit::TestFixture
{

public:
	void setUp();
	void tearDown();

	static CppUnit::Test *suite()
	{
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("ThermometerTest cases");

		// Register all test functions
		suiteOfTests->addTest(new CppUnit::TestCaller<ThermometerTest>("Prepare objects",
				&ThermometerTest::createThermometerObjects));

		suiteOfTests->addTest(new CppUnit::TestCaller<ThermometerTest>("Check objects",
				&ThermometerTest::checkThermometerObjects));

        suiteOfTests->addTest(new CppUnit::TestCaller<ThermometerTest>("Register objects",
                &ThermometerTest::registerThermometers));

		return suiteOfTests;
	}

protected:
	void createThermometerObjects();
	void checkThermometerObjects();
    void registerThermometers();

private:
	Thermometer *thermometerA;
	Thermometer *thermometerB;

};

#endif /* UNITS_THERMOMETERTEST_H_ */
