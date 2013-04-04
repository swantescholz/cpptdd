#include "Assert.h"
#include "Hacks.h"
#include "tdd.h"
//#include "ignoreTests.h"

namespace tdd {
const std::string AssertionException::unknown = "<unknown>";

string AssertionException::constructMsg(string assertion, AssertionPoint point) {
	string str = estr;
	if (!(point.func.find("__")==0)) str += point.func + " ";
	str += estr + "(" + point.file + ":" + point.line + ")" + " assertion '" + assertion + "' failed";
	return str;
}

std::string AssertionCloseException::constructMsg(double xv, std::string xstr, double yv, std::string ystr) {
	std::string str = xstr + " not-close-to " + ystr + newline;
	str += std::string("since [") + xv + "] not-close-to [" + yv + "]" + newline;
	str += std::string("( with default comparison-precision = ") + defaultPrecision + " )";
	return str;
}

std::string AssertionCloserThanException::constructMsg(double xv, std::string xstr, double yv, std::string ystr, double prec, std::string precstr) {
	std::string str = xstr + " not-close-to " + ystr + newline;
	str += std::string("since [") + xv + "] not-close-to [" + yv + "]";
	return str;
}

Test(lessThan assertion works) {
	int x = 5;
	double y = 7.0;
	assertLessThan(x,  4+2);
	assertLessThan(y, 8.0);
	assertLessThan(x, y);
}

Test(greaterThan assertion works) {
	int x = 5;
	double y = 7.0;
	assertGreaterThan(x, 6-2);
	assertGreaterThan(y, 3.0);
	assertGreaterThan(y, x);
}

Test(close assertion works) {
	try {
		assertClose(1.0,1.00001);
	} catch (...) {
		assertFail("no exception should have been thrown here")
	}
	bool failed = true;
	try {
		assertClose(1.0,1.01);
		failed = false;
	} catch (...) {}
	if (!failed) assertFail("an exception should have been thrown here")
}

Test(closerThan assertion works) {
	try {
		assertCloserThan(1.0,1.001,0.01);
	} catch (...) {
		assertFail("no exception should have been thrown here")
	}
	bool failed = true;
	try {
		assertCloserThan(1.0,1.001,0.00001);
		failed = false;

	} catch (...) {}
	if (!failed) assertFail("an exception should have been thrown here")
}
} // namespace tdd






