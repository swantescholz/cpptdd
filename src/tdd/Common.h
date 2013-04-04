#ifndef COMMON_H_
#define COMMON_H_

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <functional>

namespace tdd {

template<typename T> void print(T v) {std::cout << v;}
template<typename T> void println(T v) {std::cout << v << std::endl;}
template<typename T> void printnl(T v) {std::cout << std::endl;}

std::wstring to_wstring(const std::string& str);


#ifdef _WIN32
	const std::string newline("\r\n");
#else
	const std::string newline("\n"); // Mac OS X uses \n, Linux too
#endif



#define declstrop(T) \
	std::string& operator+=(std::string& s, T i); \
	std::string operator+(std::string s, T i); \
	std::string operator+(T i, std::string s);
declstrop(bool) declstrop(short) declstrop(int) declstrop(long long int)
declstrop(float) declstrop(double) declstrop(std::size_t)
#undef declstrop

} // namespace tdd



#endif
