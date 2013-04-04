#include "Example.h"
#include <memory>

#include "tdd/tdd.h"


Test(The first test in a file will be executed first) {
	assertTrue(true == true);
	assertFalse(false != false);
}

//To exclude a range of Tests in a file, simply add:
#include "tdd/ignoreTests.h"
Test(This second Test would fail if executed) {
	assertFail("This would normally fail")
}
Test(This third Test will also be excludes from execution) {
	assertFail("This would also fail")
}

//To activate following Tests, add:
#include "tdd/reactivateTests.h"
Test(The fourth test here will be executed correctly again) {
	//asserts are optional, but a test makes little sense without them
}

Test(How to use assertEqual) {
	assertEqual(!true, false);
	Example example;
	assertEqual(example.getFive(), 5);
}

Test(How to use assertClose) {
	assertClose(Example::pi, 3.1415926535897);
	Example example;
	assertCloserThan(example.getTen(), 10.01, 0.001);
}

Test(The assert macros throw Exceptions) {
	try {
		assertFail("this will be catched");
	} catch (std::shared_ptr<tdd::AssertionException> exception) {
		std::cout << "catched" << std::endl;
		auto ex = exception.get();
		assertEqual(ex->msg, "this will be catched");
		assertEqual(ex->getAssertionType(), "assertTrue");
	}
	std::cout << "not yet catched" << std::endl;
}

Test(The last test in a file will be executed last) {
	assertTrue(true);
}
