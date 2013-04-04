#include "Util.h"
#include "Hacks.h"
#include "tdd.h"
#include "ignoreTests.h"
#include <cmath>

namespace tdd {

Util::Util() {}
Util::~Util() {}

bool Util::almostEqual(double a, double b, double epsilon) {
	return std::abs(a - b) <= ( (std::abs(a) < std::abs(b) ? std::abs(b) : std::abs(a)) * epsilon);
}

Test(min/max works with variadic templates) {
	assertEqual(util.min(4,3,2,5), 2);
	assertClose(util.min(4.3,3.3333333,5.9), 10.0/3);
}

Test(almost equal works) {
	assertFalse(util.almostEqual(1.0,1.01));
	assertTrue(util.almostEqual(1.0,1.01,0.1));
}


} // namespace tdd




