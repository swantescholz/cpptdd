
#include "App.h"
#include "tdd.h"
#include "Hacks.h"

#include <regex>
#include <iterator>

Test(hello main) {
	int x = 9;
	assertEquals(x,9)
	//assertEquals(x,8)
	assertEquals(x+1,10)
}


void test() {
	testing.runAllTests();

}

void runApp() {
	App app;
	app.run();
}

int main(int argc, char **argv) {
	test();
	//runApp();
	
	return 0;
}


