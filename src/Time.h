#ifndef TIME_H_
#define TIME_H_

#include "Common.h"
#include "Hacks.h"
#include <chrono>

namespace tdd {

typedef std::chrono::high_resolution_clock tclock;
typedef std::chrono::microseconds microseconds;
typedef std::chrono::milliseconds milliseconds;
typedef tclock::time_point timepoint;

tclock::time_point now();
void wait(double sec);
double durationSec(const timepoint& t1, const timepoint& t2);
llint durationUs(const timepoint& t1, const timepoint& t2);
std::string indentNumber(int num, int width, char ch = ' ');
std::string formatDuration(const timepoint& t1, const timepoint& t2);

} // namespace tdd





#endif /* TIME_H_ */
