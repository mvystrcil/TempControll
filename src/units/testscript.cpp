#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
 
#include "thermometertest.h"
#include "../lib/logger.h"

Logger dbg("units.log", false);
std::string lf = "\n";
 
int main() {
	CppUnit::TextUi::TestRunner runner;
 
	dbg << "Unit tests started" << lf;
	runner.addTest(ThermometerTest::suite());
	dbg << "Running the unit tests." << lf;
	runner.run();
 
	return 0;
}
