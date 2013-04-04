#ifndef TDD_H_
#define TDD_H_

#include "Testing.h"
#include "Assert.h"

#define testing (tdd::Testing::getInstance())

#define RUN_ALL_TESTS_MAIN \
	int main(int argc, char **argv) { \
		testing.runAllTests(); \
		return 0; \
	}

#endif /* TDD_H_ */
