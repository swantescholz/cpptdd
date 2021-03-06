cpptdd
=======
A Simple Test Driven Development Toolkit for C++11
-------
## Features

- Leightweight library for Unit-Testing C++ programs
- Macro ```Test``` for automatic registration of testcases
- Predefined assertion macros like ```assertEqual``` for comfortable testing

### Requirements
This library uses some of the neat features of the new C++ standard **C++11**.
To compile the sources you will need an appropiate compiler.
Version 4.7 of g++ should suffice. 

### Usage
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

### Assert Macros
Following assert macros are available in the tests:
```c++
assertFail("Unable to open file 'example.txt'");
assertTrue( 5 < 9 );
assertFalse( 11 < 9 );
assertEqual( 3, 3 );
assertUnequal( 5, 7 );
assertLessThan( 3.2, 5.9 );
assertGreaterThan( 8.3, 5.9 );
assertClose( 3.14159265, 3.1415926535897 );
assertCloserThan( 3.1, 3.1415926535897, 0.1 );
```
Do **not** use the C-Macro ```assert``` from ```assert.h```!

### Running the Tests
To run the tests, simply compile your program and execute it.
You may want to use the included **Makefile**, like:
```
make
make run
```

### Output
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

### Examples
See [Examples](src/examples)

### License
**Very** permissive.
See [UNLICENSE.txt](UNLICENSE.txt)



