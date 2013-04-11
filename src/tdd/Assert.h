
#ifndef TDD_ASSERT_H_
#define TDD_ASSERT_H_

#include "Common.h"
#include "Util.h"

namespace tdd {

struct AssertionPoint {
	const std::string file;
	const std::string func;
	const std::string line;
};

struct Exception {
	const std::string msg;
	Exception(std::string errorMsg) : msg(errorMsg) {}
	operator std::string() const {return toString();}
	std::string toString() const {return msg;}
};

struct AssertionException : Exception {
	const std::string assertion;
	const AssertionPoint point;
	AssertionException(std::string assertion, AssertionPoint point)
	: Exception(constructMsg(assertion, point)), assertion(assertion), point(point) {}
	virtual std::string getAssertionType() {return "assertBase";}
	virtual bool isValid() {return true;}
private:
	std::string constructMsg(std::string assertion, AssertionPoint point);
public:
	static const std::string unknown;
};

struct AssertionUnknownException : AssertionException {
	AssertionUnknownException()
	: AssertionException("A non-assertion exception has been thrown.\nThis is not supposed to happen!", AssertionPoint{unknown, unknown, unknown}) {}
	virtual std::string getAssertionType() {return "<unexpected exception>";}
};

struct AssertionTrueException : AssertionException {
	AssertionTrueException(std::string assertion, AssertionPoint point)
	: AssertionException(assertion + " != true", point) {}
	virtual std::string getAssertionType() {return "assertTrue";}
};

struct AssertionFalseException : AssertionException {
	AssertionFalseException(std::string assertion, AssertionPoint point)
	: AssertionException(assertion + " != false", point) {}
	virtual std::string getAssertionType() {return "assertFalse";}
};

struct AssertionFailException : AssertionException {
	AssertionFailException(std::string failDescription, AssertionPoint point)
	: AssertionException(failDescription, point) {}
	virtual std::string getAssertionType() {return "assertFail";}
};

template<typename X, typename Y>
struct AssertionEqualException : AssertionException {
	AssertionEqualException(X xv, std::string xstr, Y yv, std::string ystr, AssertionPoint point)
	: AssertionException(constructMsg(xv,xstr,yv,ystr), point) {}
	virtual std::string getAssertionType() {return "assertEqual";}
private:
	std::string constructMsg(X xv, std::string xstr, Y yv, std::string ystr) {
		std::string str = xstr + " != " + ystr + newline;
		str += std::string("since [") + xv + "] != [" + yv + "]";
		return str;
	}
};

template<typename X, typename Y>
struct AssertionUnequalException : AssertionException {
	AssertionUnequalException(X xv, std::string xstr, Y yv, std::string ystr, AssertionPoint point)
	: AssertionException(constructMsg(xv,xstr,yv,ystr), point) {}
	virtual std::string getAssertionType() {return "assertUnequal";}
private:
	std::string constructMsg(X xv, std::string xstr, Y yv, std::string ystr) {
		std::string str = xstr + " == " + ystr + newline;
		str += std::string("since [") + xv + "] == [" + yv + "]";
		return str;
	}
};

template<typename X, typename Y>
struct AssertionLessThanException : AssertionException {
	AssertionLessThanException(X xv, std::string xstr, Y yv, std::string ystr, AssertionPoint point)
	: AssertionException(constructMsg(xv,xstr,yv,ystr), point) {}
	virtual std::string getAssertionType() {return "assertLessThan";}
private:
	std::string constructMsg(X xv, std::string xstr, Y yv, std::string ystr) {
		std::string str = xstr + " >= " + ystr + newline;
		str += std::string("since [") + xv + "] >= [" + yv + "]";
		return str;
	}
};

template<typename X, typename Y>
struct AssertionGreaterThanException : AssertionException {
	AssertionGreaterThanException(X xv, std::string xstr, Y yv, std::string ystr, AssertionPoint point)
	: AssertionException(constructMsg(xv,xstr,yv,ystr), point) {}
	virtual std::string getAssertionType() {return "assertGreaterThan";}
private:
	std::string constructMsg(X xv, std::string xstr, Y yv, std::string ystr) {
		std::string str = xstr + " <= " + ystr + newline;
		str += std::string("since [") + xv + "] <= [" + yv + "]";
		return str;
	}
};

struct AssertionCloseException : AssertionException {
	AssertionCloseException(double xv, std::string xstr, double yv, std::string ystr, AssertionPoint point)
	: AssertionException(constructMsg(xv,xstr,yv,ystr), point) {}
	virtual std::string getAssertionType() {return "assertClose";}
	static constexpr double defaultPrecision = Util::defaultEpsilon;
private:
	std::string constructMsg(double xv, std::string xstr, double yv, std::string ystr);
};

struct AssertionCloserThanException : AssertionException {
	AssertionCloserThanException(double xv, std::string xstr, double yv, std::string ystr, double prec, std::string precstr, AssertionPoint point)
	: AssertionException(constructMsg(xv,xstr,yv,ystr,prec,precstr), point) {}
	virtual std::string getAssertionType() {return "assertCloserThan";}
private:
	std::string constructMsg(double xv, std::string xstr, double yv, std::string ystr, double prec, std::string precstr);
};


template<typename T> void __mythrow(const T& v) {throw std::shared_ptr<AssertionException>(new T(v));}

} // namespace tdd

#define __FFL tdd::AssertionPoint{__FILE__,__func__,std::to_string(__LINE__)}
#define assertFail(X) tdd::__mythrow(tdd::AssertionFailException(std::string(X),__FFL));
#define assertTrue(X) if (!(X)) {tdd::__mythrow(tdd::AssertionTrueException(#X,__FFL));}
#define assertFalse(X) if (X) {tdd::__mythrow(tdd::AssertionFalseException(#X,__FFL));}
#define assertEqual(X,Y) {auto __x = (X); auto __y = (Y); if (!(__x == __y)) { \
	tdd::__mythrow(tdd::AssertionEqualException<decltype(__x),decltype(__y)>(__x,#X,__y,#Y,__FFL));}}
#define assertUnequal(X,Y) {auto __x = (X); auto __y = (Y); if (!(__x != __y)) { \
	tdd::__mythrow(tdd::AssertionUnequalException<decltype(__x),decltype(__y)>(__x,#X,__y,#Y,__FFL));}}
#define assertLessThan(X,Y) {auto __x = (X); auto __y = (Y); if (!(__x < __y)) { \
	tdd::__mythrow(tdd::AssertionLessThanException<decltype(__x),decltype(__y)>(__x,#X,__y,#Y,__FFL));}}
#define assertGreaterThan(X,Y) {auto __x = (X); auto __y = (Y); if (!(__x > __y)) { \
	tdd::__mythrow(tdd::AssertionGreaterThanException<decltype(__x),decltype(__y)>(__x,#X,__y,#Y,__FFL));}}
#define assertClose(X,Y) {auto __x = (X); auto __y = (Y); if (!tdd::Util::getInstance().almostEqual(__x,__y)) { \
	tdd::__mythrow(tdd::AssertionCloseException(__x,#X,__y,#Y,__FFL));}}
#define assertCloserThan(X,Y,PRECISION) {auto __x = (X); auto __y = (Y); auto __precision = (PRECISION); if (!tdd::Util::getInstance().almostEqual(__x,__y,__precision)) { \
	tdd::__mythrow(tdd::AssertionCloserThanException(__x,#X,__y,#Y,__precision,#PRECISION,__FFL));}}



#endif
