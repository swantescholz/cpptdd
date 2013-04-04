
#ifndef ASSERT_H_
#define ASSERT_H_

#include "Common.h"
#include "Util.h"

struct AssertionPoint {
	const std::string file;
	const std::string func;
	const std::string line;
};

struct Exception {
	std::string msg;
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
struct AssertionEqualsException : AssertionException {
	AssertionEqualsException(X xv, std::string xstr, Y yv, std::string ystr, AssertionPoint point)
	: AssertionException(constructMsg(xv,xstr,yv,ystr), point) {}
	virtual std::string getAssertionType() {return "assertEquals";}
private:
	std::string constructMsg(X xv, std::string xstr, Y yv, std::string ystr) {
		std::string str = xstr + " != " + ystr + newline;
		str += std::string("since [") + xv + "] != [" + yv + "]";
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
	virtual std::string getAssertionType() {return "assertClose";}
private:
	std::string constructMsg(double xv, std::string xstr, double yv, std::string ystr, double prec, std::string precstr);
};



#define _FFL AssertionPoint{__FILE__,__func__,std::to_string(__LINE__)}
#define assertTrue(X) if (!(X)) {throw new AssertionTrueException(#X,_FFL);}
#define assertFalse(X) if (X) {throw new AssertionFalseException(#X,_FFL);}
#define assertFail(X) throw new AssertionFailException(std::string(X),_FFL);
#define assertEquals(X,Y) {auto __x = (X); auto __y = (Y); if (!(__x == __y)) \
	throw new AssertionEqualsException<decltype(__x),decltype(__y)>(__x,#X,__y,#Y,_FFL);}
#define assertLessThan(X,Y) {auto __x = (X); auto __y = (Y); if (!(__x < __y)) \
	throw new AssertionLessThanException<decltype(__x),decltype(__y)>(__x,#X,__y,#Y,_FFL);}
#define assertGreaterThan(X,Y) {auto __x = (X); auto __y = (Y); if (!(__x > __y)) \
	throw new AssertionGreaterThanException<decltype(__x),decltype(__y)>(__x,#X,__y,#Y,_FFL);}
#define assertClose(X,Y) {auto __x = (X); auto __y = (Y); if (!util.almostEqual(__x,__y)) \
	throw new AssertionCloseException(__x,#X,__y,#Y,_FFL);}
#define assertCloserThan(X,Y,PRECISION) {auto __x = (X); auto __y = (Y); auto __precision = (PRECISION); if (!util.almostEqual(__x,__y,__precision)) \
	throw new AssertionCloserThanException(__x,#X,__y,#Y,__precision,#PRECISION,_FFL);}


#endif
