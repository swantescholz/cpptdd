#ifndef TESTCASE_H_
#define TESTCASE_H_

#include "Common.h"
#include "Assert.h"

namespace tdd {

typedef std::function<void(void)> func_t;

class Testcase {
public:
	std::string name,file;
	std::string linenumber;
	func_t func;
	std::shared_ptr<AssertionException> failedAssertion;

	bool hasFailed() {return failedAssertion != nullptr;}
	std::string getErrorDescription(std::string indentString);

	operator std::string() const {return toString();}
	std::string toString() const {return file + ": '" + name + "'";}
	std::string toShortString() const {return "" + name + "";}

	Testcase(std::string testcaseName, std::string testcaseFile, std::string linenumber, func_t f)
	 : name(testcaseName), file(testcaseFile), linenumber(linenumber), func(f) {}
};

} // namespace tdd





#endif /* TESTCASE_H_ */
