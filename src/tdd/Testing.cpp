#include "Testing.h"
#include "Hacks.h"
#include "Util.h"
#include "String.h"

#include <algorithm>

namespace tdd {

Testing::Testing() {
	outputWidth = 120;
	minTestrunResultIndentation = 40;
	indentString = "    ";
	shortenFilepaths = true;
}

void Testing::addTestcase(Testcase testcase) {
	//println("registering test: '" + testcase.name + "'");
	testcases[testcase.file].push_back(testcase);
}

int Testing::getTestCount() {
	int count = 0;
	for (auto testfile : testcases) {
		count += testfile.second.size();
	}
	return count;
}

string Testing::createLine(string s) {
	string tmp = "";
	forito(outputWidth) {
		tmp += s;
	}
	return tmp;
}

void Testing::runAllTests() {
	println(createLine("="));
	pln(estr + "RUNNING ALL TESTS (" + testcases.size() + " testfiles with " + testCountToString(getTestCount()) + ")")
	vector<string> keys;
	for (auto entry : testcases) {
		keys.push_back(entry.first);
	}
	auto cmp = [](String a, String b) {
		a = a.toLower();
		b = b.toLower();
		return a.compare(b) < 0;
	};
	sort(keys.begin(),keys.end(), cmp);
	for (auto key : keys) {
		runTestfile(key);
	}
	printStatistic();
}

void Testing::printStatistic() {
	string str = "";
	str += createLine("=") + nl;
	str += "FAILED ASSERTIONS:";

	int nFailedTests = 0;
	for (auto test : runTests) {
		if (test.hasFailed()) {
			nFailedTests++;
			str += nl + createLine("-");
			str += nl + test.getErrorDescription(indentString);
		}
	}
	if (nFailedTests <= 0) {
		str += " none";
	}

	str += nl + createLine("=") + nl;
	str += estr + "Ran " + getTestPercentage() + ", ";
	str += testCountToString(nFailedTests) + " failed." + nl;
	if (nFailedTests > 0)
		str += ">>> RED <<<" + nl;
	else 
		str += "__ GREEN __" + nl;
	print(str);
}

string Testing::getTestPercentage() {
	int nRunTests = runTests.size();
	string str = estr + "(" + nRunTests + "/" + getTestCount() + ") test";
	if (nRunTests != 1) str += "s";
	return str;
}

void Testing::runTestfile(string filename) {
	auto tests = testcases[filename];
	String printedFilename = filename;
	if (self.shortenFilepaths) {
		printedFilename = printedFilename.extractTail("/");
	}
	println("" + printedFilename + " (" + testCountToString(tests.size()) + ")");
	int longestNameLength = 0;
	for (auto test : tests) {
		if (int(test.name.length()) > longestNameLength) {
			longestNameLength = test.name.length();
		}
	}
	for (auto test : tests) {
		runTestcase(test, longestNameLength);
	}
}

string Testing::testCountToString(int count) {
	if (count <= 0) return "no tests";
	if (count == 1) return "1 test";
	return count + string(" tests");
}

void Testing::runTestcase(Testcase testcase, int longestNameLength) {
	bool failed = true;
	try {
		String line = indentString + testcase.toShortString() + " ";
		int numDots = 3; // + longestNameLength - testcase.name.length();
		numDots = util.max(numDots, minTestrunResultIndentation - line.lengthInCharacters());
		forito(numDots) {
			line += ".";
		}
		line += " ";
		print(line);
		testcase.func();
		failed = false;
	} catch (const shared_ptr<AssertionException>& ex) {
		testcase.failedAssertion = ex;
	} catch (...) {
		testcase.failedAssertion.reset(new AssertionUnknownException());
	}
	if (failed) {
		println("failed");
	} else {
		println("done");
	}
	runTests.push_back(testcase);
}


} // namespace tdd


