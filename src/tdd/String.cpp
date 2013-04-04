#include "String.h"
#include "Testing.h"
#include "ignoreTests.h"
#include "Hacks.h"

#include <algorithm>

namespace tdd {

const String String::whitespaceCharacters(" \t\n\r");

String::String(const std::vector<String>& strs, const String& delim) {
	self = "";
	for(auto str : strs) {
		self += str + delim;
	}
	if (!self.empty()) {
		self.erase(self.lengthInBytes()-delim.lengthInBytes());
	}
}
bool String::startsWith(const String& s) const {return find(s) == 0;}
bool String::endsWith(const String& s) const {return static_cast<int>(find_last_of(s)) == self.lengthInBytes()-1;}
bool String::contains(const String& s) const {return find(s) != string::npos;}

String String::replaceAll(const String& oldString, const String& newString) const {
	String str(*this);
	int pos = 0, la = oldString.lengthInBytes(), lb = newString.lengthInBytes();
	for (;;) {
		pos = str.find(oldString, pos);
		if (pos == npos) break;
		str.replace(pos, la, newString);
		pos += lb;
	}
	return str;
}

String String::extractTail(const String& after) const {
	int pos = self.find_last_of(after);
	return self.substr(pos + 1);
}

String String::repeat(int times, const String& delim) const {
	String repeated;
	forito(times) {
		repeated += self;
		if (i+1 < times) {
			repeated += delim;
		}
	}
	return repeated;
}

std::vector<String> String::toLines() const {
	return self.split(newline,-1);
}
std::vector<String> String::split(const String& where, int maxTimes) const {
	std::vector<String> parts;
	const int lenWhere = where.lengthInBytes();
	int pos = 0;
	int times = 0;
	for(;;) {
		int oldPos = pos;
		pos = self.find(where, pos);
		String item;
		if (pos == npos) {
			item = self.substr(oldPos);
		} else {
			item = self.substr(oldPos, pos-oldPos);
		}
		parts.push_back(item);
		times++;
		if (times == maxTimes || pos == npos) break;
		pos += lenWhere;
	}
	return parts;
}
int String::lengthInBytes() const {
	return static_cast<int>(self.size());
}
int String::lengthInCharacters() const {
	//counting utf8 correctly now:
	int count = 0;
	for (char c : self) {
		if ((c & 0xc0) != 0x80) count++;
	}
	return count;
}
bool String::isWhitespace() const {
	return self.find_first_not_of(whitespaceCharacters) == string::npos;
}


String String::trimWhitespace(bool front, bool middle, bool back) const {
	String s = self;
	if (front) {
		int firstNonwhitePos = s.find_first_not_of(whitespaceCharacters);
		s = s.substr(firstNonwhitePos);
	}
	if (back) {
		int lastNonwhitePos = s.find_last_not_of(whitespaceCharacters);
		s = s.substr(0,lastNonwhitePos + 1);
	}
	if (middle) {
		for (int i = 0; i < s.lengthInBytes(); ++i) {
			if (whitespaceCharacters.contains(s[i])) {
				s[i] = ' ';
			}
		}
		int lenFront = s.find_first_not_of(whitespaceCharacters);
		int lenBack = s.lengthInBytes() - s.find_last_not_of(whitespaceCharacters) - 1;
		if (lenFront == npos) lenFront = 0;
		if (lenBack == npos) lenBack = 0;
		for(;;) {
			int index = s.find("  ", lenFront);
			if (index >= s.lengthInBytes() - lenBack or index == npos) break;
			s.erase(index,1);
		}
	}
	return s;
}

String String::removeEnding(const String& ending) const {
	if (self.endsWith(ending)) {
		return self.substr(0,self.lengthInBytes() - ending.lengthInBytes());
	}
	return self;
}

String String::breakLines(int maxLength) const {
	vector<String> lines;
	String line = "";
	for (int i = 0; i < self.lengthInBytes(); ++i) {
		String ch = String(self.at(i));
		line += ch;
		if (line.isWhitespace()) line.clear();
		bool isLineTooLong = line.lengthInCharacters() > maxLength and ch.isWhitespace();
		bool wasNewline = ch == "\n";
		if (isLineTooLong or wasNewline) {
			line = line.trimWhitespace(true,false,true);
			lines.push_back(line);
			line.clear();
		}
	}
	if (!line.empty()) {
		lines.push_back(line);
	}
	return String(lines);
}

String String::toLower() const {
	String s(self);
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

String String::toUpper() const {
	String s(self);
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}

Test(toLower works) {
	assertEqual(String(".-AbXy").toLower(), ".-abxy");
}
Test(toUpper works) {
	assertEqual(String(".-AbXy").toUpper(), ".-ABXY");
}
Test(breakLines works) {
	String s = "aaaaa bbbbb ccccc ddd eee fff ggg";
	s = s.repeat(2,nl);
	String broken = s.breakLines(15);
	auto lines = broken.toLines();
	assertEqual(static_cast<int>(lines.size()), 4);
	assertEqual(lines[0], "aaaaa bbbbb ccccc");
	assertEqual(lines[1], "ddd eee fff ggg");
	assertEqual(lines[2], lines[0]);
	assertEqual(lines[3], lines[1]);
}

Test(constants are correct) {
	assertTrue(String::whitespaceCharacters.contains(" "));
	assertTrue(String::whitespaceCharacters.contains("\n"));
	assertTrue(String::whitespaceCharacters.contains("\t"));
	assertTrue(String::whitespaceCharacters.contains("\r"));
	assertEqual(String::npos, static_cast<int>(string::npos));
}
Test(removeEnding works) {
	assertEqual(String("hello.txt").removeEnding(".txt"), "hello");
	assertEqual(String("hello.exe").removeEnding(".txt"), "hello.exe");
}


Test(trimming whitespace works) {
	assertEqual(String("  xx    yy  ").trimWhitespace(true,false,false), "xx    yy  ");
	assertEqual(String("  xx    yy  ").trimWhitespace(false,false,true), "  xx    yy");
	assertEqual(String("  xx    yy  ").trimWhitespace(false,true,false), "  xx yy  ");
	assertEqual(String("\r\n \t\n \t xx    yy\n\t\r \t  ").trimWhitespace(true,true,true), "xx yy");
	assertEqual(String("a\t\nb   c\t\r   de").trimWhitespace(false,true,false), "a b c de");
}

Test(check whitespace works) {
	assertTrue(String("\t\n  \r\n").isWhitespace());
	assertFalse(String("\txx\n  \t\n").isWhitespace());
}

Test(length works) {
	String s("abc wert");
	assertEqual(s.lengthInCharacters(), 8)
}

Test(unicode string length behaves as expected) {
	String asciiChars  = "abcdefgh";
	String germanChars = "äöüÄÖÜß€";
	String mathChars   = "¬∧∈∀∨∃⇔⇒";
	int expectedLength = 8;
	assertEqual(asciiChars.lengthInCharacters(), expectedLength);
	assertEqual(germanChars.lengthInCharacters(), expectedLength);
	assertEqual(mathChars.lengthInCharacters(), expectedLength);
}

Test(line constructor works) {
	vector<String> v = {"aa","bb","cc"};
	String s(v,"xx");
	assertEqual(s,"aaxxbbxxcc");
	v.clear();
	try {
		String s2(v,"xx");
		assertEqual(s2,"");
	} catch (...) {
		assertFail("line constructer with empty vector throws exception!")
	}
}

Test(repeat works) {
	String s("ab");
	assertEqual(s.repeat(3), "ababab");
	assertEqual(s.repeat(3,"xy"), "abxyabxyab");
}

Test(toLines works) {
	String s("ab" + nl + "cd" + nl + "ef");
	auto lines = s.toLines();
	assertEqual(static_cast<int>(lines.size()), 3);
	assertEqual(lines[0], "ab");
	assertEqual(lines[1], "cd");
	assertEqual(lines[2], "ef");
}

Test(split works) {
	String s("abxycdxyef");
	auto parts = s.split("xy");
	assertEqual(static_cast<int>(parts.size()), 3);
	assertEqual(parts[0], "ab");
	assertEqual(parts[1], "cd");
	assertEqual(parts[2], "ef");
	parts = s.split("xy", 2);
	assertEqual(static_cast<int>(parts.size()), 2);
	assertEqual(parts[0], "ab");
	assertEqual(parts[1], "cd");
}


Test(extractTail works) {
	assertEqual(String("/hello world/blabla/foobar.txt").extractTail("/"), "foobar.txt");
	assertEqual(String("xxfooxxfooar.txt").extractTail("foo"), "ar.txt");
	assertEqual(String("aabbcc.txt").extractTail("/"), "aabbcc.txt");
}

Test(replaceAll works) {
	String s("xxbxxcxxdxx");
	s = s.replaceAll("xx","xax");
	assertEqual(s,"xaxbxaxcxaxdxax");
}
Test(contains works) {
	String s("abc wert");
	assertTrue(s.contains("bc w"));
}

Test(hello xx   ss string dsf sdf sdkjfh skfjh sdkfjhsd kajfhkjsa dhkdjsfh
		sdfsdfsdf sdfkjhsd dsf ) {
	int x = 8;
	assertEqual(x,8)
	assertEqual(x+1,9)
	assertFalse(x < 7)
}

Test(starts with works) {
	String s("abc wert");
	assertTrue(s.startsWith("ab"))
	assertFalse(s.startsWith("we"))
}

Test(ends with works) {
	String s("abc wert");
	assertTrue(s.endsWith("ert"))
	assertFalse(s.endsWith("wer"))
}


} // namespace tdd








