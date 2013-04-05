#include "Example.h"
#include <memory>

#include "tdd/tdd.h"

//It's best to put the complex tests into a seperate file called
//<your-class-name>Test.cpp e.g. ExampleTest.cpp

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

Test(How to use assertUnequal) {
	assertUnequal(true, false);
	assertUnequal(Example::pi, 2.2);
}

Test(How to use assertLess) {
	assertLessThan(Example::pi, 5.5);
}
Test(How to use assertGreater) {
	assertGreaterThan(Example::pi, 2.5);
}

Test(How to use assertClose) {
	// The default precision is tdd::Util::defaultEpsilon (0.0001)
	assertClose(Example::pi, 3.1415926535897);
}

Test(How to use assertCloserThan) {
	Example example;
	// assertClose and assertCloserThan work with a relative precision:
	// Instead of an absolute check: assert |B-A| < precision (0.005),
	// it works like this: assert |B-A| / A < precision (0.5%)
	double precision = 0.005;
	assertCloserThan(example.getTen(), 10.01, precision);
}

//if you want to have characters like tab and "," in your test names, use TestWithQuotedName:
TestWithQuotedName("This quoted test name can have   wide\tgaps and many, many, many \",\"s and also \";\", \"'\", \"&\", etc.") {
	bool cool = true;
	assertTrue(cool);
}

//using unicode characters as test names is discouraged, I recommend to use :
//ae for ä, oe for ö, ue for ü, ss for ß, EUR for €, hello for 你好 etc.
//if really, really want to use unicode characters, this should - depending on your compiler and file encoding - (probably) work:
//TestWithQuotedName("Unicode works: ä,ö,ü,Ä,Ö,Ü,ß,€,∀,¬,∈") {}

//You can write long test name in multiple lines without problems:
Test(Test names that //each newline will be replaced with a single space
		stretch over multiple lines
		are also
		very possible) {
	assertTrue(true);
}
TestWithQuotedName("Another way of" \
		" creating long test names" \
		" over multiple lines") {
	assertTrue(true);
}


//keywords in test names are now problem at all
Test(The assert macros throw Exceptions that can be examined) {
	try {
		assertFail("this will be catched");
	} catch (std::shared_ptr<tdd::AssertionException> exception) {
		auto ex = exception.get();
		assertTrue(ex->msg.find("this will be catched") != std::string::npos);
		assertEqual(ex->getAssertionType(), "assertFail");
	}
}

Test(The last test in a file will be executed last) {
	assertTrue(true);
}
