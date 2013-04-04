#include "Testcase.h"
#include "Hacks.h"
#include "String.h"

namespace tdd {

string Testcase::getErrorDescription(string indentString) {
	if (failedAssertion == nullptr) return "";
	AssertionPoint point = failedAssertion->point;
	string usedFilename = point.file;
	string usedLinenumber = point.line;
	auto check = [](string& sofar, string strdefault) {
		if (sofar == AssertionException::unknown)
			sofar = strdefault;
	};
	check(usedFilename, file);
	check(usedLinenumber, linenumber);

	string str = "";
	str += "Test  : " + name + nl;
	str += "From  : " + usedFilename + nl;
	str += "Line  : " + usedLinenumber + nl;
	str += "Type  : " + failedAssertion->getAssertionType() + nl;
	str += "Cause :" + nl;
	String msg = failedAssertion->assertion;
	str += indentString + msg.replaceAll(nl,nl+indentString);
	return str;
}


} // namespace tdd


