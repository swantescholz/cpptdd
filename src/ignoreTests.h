#ifndef IGNORETESTS_H_
#define IGNORETESTS_H_

#ifdef Test
	#undef Test
#endif
#ifdef IGNORE_TESTS
	#undef IGNORE_TESTS
#endif

class __IgnoreDummy {
public:
	__IgnoreDummy(std::function<void(void)> f) {}
};

#define Test(X) \
	static void STRING_JOIN(__testcasefunc,__LINE__)(); \
	static __IgnoreDummy STRING_JOIN(__testcasedummy,__LINE__)(STRING_JOIN(__testcasefunc,__LINE__)); \
	static void STRING_JOIN(__testcasefunc,__LINE__)()
#define IGNORE_TESTS

#endif /* IGNORETESTS_H_ */
