#include "Time.h"

tclock::time_point now() {return tclock::now();}
void wait(double sec) {std::this_thread::sleep_for(microseconds((int)(sec*1000000.0)));}
double durationSec(const timepoint& t1, const timepoint& t2) {
	return chrono::duration_cast<microseconds>(t2 - t1).count() / 1000000.0;
}
llint durationUs(const timepoint& t1, const timepoint& t2) {
	return chrono::duration_cast<microseconds>(t2 - t1).count();
}
string indentNumber(int num, int width, char ch) {
	string tmp, s = string("") + num;
	forito(width - s.length()) {tmp += ch;}
	return tmp+s;
}
string formatDuration(const timepoint& t1, const timepoint& t2) {
	llint us = durationUs(t1,t2);
	llint ms = us / 1000; us %= 1000;
	int s = ms / 1000; ms %= 1000;
	int m = s / 60; s %= 60;
	int h = m / 60; s %= 60;
	string str = "";
	auto f = [](int x, int w){return indentNumber(x,w,'0');};
	if (h     > 0) str += f(h,2) + ":";
	if (h+m   > 0) str += f(m,2) + ":";
	if (h+m+s > 0) str += f(s,2);
	else str += s;
	str += "."+f(ms,3);
	return str;
}
