
#include "undefineTestMacros.h"

#define TestWithQuotedName(X) \
	static void STRING_JOIN(__testcasefunc,__LINE__)(); \
	static tdd::__TestDummy STRING_JOIN(__testcasedummy,__LINE__)(X,__FILE__,__LINE__,STRING_JOIN(__testcasefunc,__LINE__)); \
	static void STRING_JOIN(__testcasefunc,__LINE__)()
#define Test(X) TestWithQuotedName(#X)
