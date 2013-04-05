
#include "examples/Example.h"
#include "tdd/tdd.h"


//you can put tests in your main.cpp file if you really want to
Test(one test from main.cpp) {
	int x = 9;
	assertEqual(x,9)
}

// =======================
// === EXECUTING TESTS ===

//EITHER manually configure how and which tests to run:
int main(int argc, char **argv) {
	testing.setOutputWidth(100); //the length of the seperation lines
	testing.setDefaultTestrunResultIndentation(50); //controls the maximum number of dots in "... done"
	testing.runAllTests(); //this will run all testfiles in alphabetical order
	return 0;
}
//OR simply run all tests with this shortcut:
//RUN_ALL_TESTS_MAIN


