
#include "undefineTestMacros.h"

#define TestWithQuotedName(X) \
	static void STRING_JOIN(__testcasefunc,__LINE__)(); \
	static tdd::__TestIgnoreDummy STRING_JOIN(__testcasedummy,__LINE__)(STRING_JOIN(__testcasefunc,__LINE__)); \
	static void STRING_JOIN(__testcasefunc,__LINE__)()
#define Test(X) TestWithQuotedName(#X)
#define IGNORE_TESTS



