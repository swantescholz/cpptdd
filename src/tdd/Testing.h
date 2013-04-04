#ifndef TESTING_H_
#define TESTING_H_

#include "Singleton.h"
#include "Assert.h"
#include "Common.h"
#include "Macros.h"
#include "Testcase.h"

namespace tdd {

class Testing : public Singleton<Testing> {
public:
	Testing();
	std::map<std::string,std::vector<Testcase> > testcases;
	void addTestcase(Testcase testcase);
	
	void runAllTests();
	void runTestfile(std::string filename);
	int getTestCount();
	void printStatistic();

	void setOutputWidth(int width) {outputWidth = width;}
	int getOutputWidth() {return outputWidth;}
	void setDefaultTestrunResultIndentation(int width) {minTestrunResultIndentation = width;}
	int getDefaultTestrunResultIndentation() {return minTestrunResultIndentation;}
private:
	void runTestcase(Testcase testcase, int longestNameLength);
	std::string testCountToString(int cound);
	std::string getTestPercentage();
	std::string createLine(std::string s);
	std::vector<Testcase> runTests;

	int outputWidth;
	int minTestrunResultIndentation;
	std::string indentString;
	bool shortenFilepaths;
};

class __TestDummy {
public:
	__TestDummy(std::string testcaseName, std::string fileName, int linenumber, func_t f) {
		Testing::getInstance().addTestcase(Testcase(testcaseName, fileName, std::to_string(linenumber),f));
	}
};

class __TestIgnoreDummy {
public:
	__TestIgnoreDummy(std::function<void(void)> f) {}
};

} // namespace tdd


#ifndef IGNORE_TESTS
#include "reactivateTests.h"
#endif

#endif


