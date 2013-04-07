cpptdd
=======
A Simple Test Driven Development Toolkit for C++11
-------
###Features

- Leightweight library for Unit-Testing C++ programs
- Macro ```Test``` for automatic registration of testcases
- Predefined assertion macros like ```assertEquals``` for comfortable testing

###Usage
```c++
#include "tdd/tdd.h"

//you can put tests in your main.cpp file if you want to
Test(one test from main.cpp) {
	int x = 9;
	assertEqual(x, 8);
}

int main(int argc, char **argv) {
	testing.runAllTests();
	return 0;
}
```

###Output
The output of **cpptdd** looks like this:
```
============================================================
RUNNING ALL TESTS (3 testfiles with 15 tests)
Example.cpp (1 test)
    A first short test in Example.cpp ............ done
ExampleTest.cpp (13 tests)
    The first test in a file will be executed first ... done
    The fourth test here will be executed correctly again ... done
    How to use assertEqual ....................... done
    How to use assertUnequal ..................... done
    How to use assertLess ........................ done
    How to use assertGreater ..................... done
    How to use assertClose ....................... done
    How to use assertCloserThan .................. done
    This quoted test name can have   wide	gaps and many, many, many ","s and also ";", "'", "&", etc. ... done
    Test names that stretch over multiple lines are also very possible ... done
    Another way of creating long test names over multiple lines ... done
    The assert macros throw Exceptions that can be examined ... done
    The last test in a file will be executed last ... done
main.cpp (1 test)
    one test from main.cpp ....................... failed
============================================================
FAILED ASSERTIONS:
------------------------------------------------------------
Test  : one test from main.cpp
From  : src/main.cpp
Line  : 7
Type  : assertEqual
Cause :
    x != 8
    since [9] != [8]
============================================================
Ran (15/15) tests, 1 test failed.
>>> RED <<<
```

###Examples
See [Examples](src/examples)

###License
See [UNLICENSE.txt](UNLICENSE.txt)



