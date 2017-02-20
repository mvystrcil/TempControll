#include <iostream>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
 
#include "ThermometerTest.h"
 
using namespace std;
 
int main() {
	CppUnit::TextUi::TestRunner runner;
 
	cout << "Unit tests started" << endl;
	runner.addTest(ThermometerTest::suite());
	cout << "Running the unit tests." << endl;
	runner.run();
 
	return 0;
}
