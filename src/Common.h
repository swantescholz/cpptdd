#ifndef COMMON_H_
#define COMMON_H_

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <functional>
#include <thread>

template<typename T> void print(T v) {std::cout << v;}
template<typename T> void println(T v) {std::cout << v << std::endl;}
template<typename T> void printnl(T v) {std::cout << std::endl;}

std::wstring to_wstring(const std::string& str);


#ifdef _WIN32
	const std::string newline("\r\n");
#elif defined macintosh // OS 9
	const std::string newline("\r");
#else
	const std::string newline("\n"); // Mac OS X uses \n, Linux too
#endif



#define __declstrop(T) \
	std::string& operator+=(std::string& s, T i); \
	std::string operator+(std::string s, T i); \
	std::string operator+(T i, std::string s);
__declstrop(bool) __declstrop(short) __declstrop(int) __declstrop(long long int)
__declstrop(float) __declstrop(double) __declstrop(std::size_t)

#endif
