#ifndef IGNORETESTS_H_
#define IGNORETESTS_H_

#ifdef Test
#undef Test
#endif
#ifdef TestWithQuotedName
#undef TestWithQuotedName
#endif
#ifdef IGNORE_TESTS
#undef IGNORE_TESTS
#endif

namespace tdd {

class __IgnoreDummy {
public:
	__IgnoreDummy(std::function<void(void)> f) {}
};

} // namespace tdd

#define TestWithQuotedName(X) \
	static void STRING_JOIN(__testcasefunc,__LINE__)(); \
	static tdd::__IgnoreDummy STRING_JOIN(__testcasedummy,__LINE__)(STRING_JOIN(__testcasefunc,__LINE__)); \
	static void STRING_JOIN(__testcasefunc,__LINE__)()
#define Test(X) TestWithQuotedName(#X)
#define IGNORE_TESTS

#endif /* IGNORETESTS_H_ */
