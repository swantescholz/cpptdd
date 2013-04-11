#ifndef TDD_STRING_H_
#define TDD_STRING_H_

#include "Common.h"

namespace tdd {

class String : public std::string {
public:
	static constexpr int npos = std::string::npos;
	static const String whitespaceCharacters;

	String() {}
	String(const std::vector<String>& strs, const String& delim = newline);
	String(const String& s) : std::string(s) {}
	String(const std::string& s) : std::string(s) {}
	String(const char* s) : std::string(s) {}
	String(const char s) : std::string(std::string("") + s) {}
	operator std::string() const {return toString();}
	std::string toString() const {return *this;}
	
	String toLower() const;
	String toUpper() const;
	bool isWhitespace() const;
	String trimWhitespace(bool front, bool middle, bool back) const;
	int length() const = delete;
	int lengthInBytes() const;
	int lengthInCharacters() const;
	bool startsWith(const String& s) const;
	bool endsWith(const String& s) const;
	bool contains(const String& s) const;
	String replaceAll(const String& oldString, const String& newString) const;
	String extractTail(const String& after) const;
	String repeat(int times, const String& delim = "") const;
	std::vector<String> toLines() const;
	std::vector<String> split(const String& where, int maxTimes = -1) const;
	String breakLines(int maxLength) const;
	String removeEnding(const String& ending) const;
};

} // namespace tdd





#endif
