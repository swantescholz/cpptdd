#include "Example.h"

//each Testfile must include the following line:
#include "tdd/tdd.h"

//you can put Tests directly into you class's cpp-file if you want
Test(A first short test in Example.cpp) {
	assertTrue(true) //the semicolon is optional
	assertFalse(false); //you can use multiple asserts in one test
}




Example::Example() {}
Example::~Example() {}

int Example::getFive() {
	return 5;
}
double Example::getTen() {
	return 10.0;
}

