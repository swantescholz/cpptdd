
#ifndef UTIL_H_
#define UTIL_H_

#include "Common.h"
#include "Singleton.h"

class Util : public Singleton<Util> {
public:
	Util();
	~Util();

	static constexpr double defaultEpsilon = 0.0001;

	template<typename T> T min(T a) {return a;}
	template<typename T> T max(T a) {return a;}
	template<typename T, typename... Args> T min(T a, Args... args) {T b = min(args...); if (b < a) return b; return a;}
	template<typename T, typename... Args> T max(T a, Args... args) {T b = max(args...); if (b > a) return b; return a;}

	bool almostEqual(double a, double b, double epsilon = defaultEpsilon);


};

#endif /* UTIL_H_ */
