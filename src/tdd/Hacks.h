#ifndef HACKS_H_
#define HACKS_H_

#include "Common.h"
#include "Macros.h"

namespace tdd {

using namespace std;

#define util (Util::getInstance())

struct ScopeExit {
    ScopeExit(std::function<void(void)> g) : f(g) {}
    ~ScopeExit() { f(); }
    std::function<void(void)> f;
};

#define fora(X,Y,Z) for(int X = (Y), z=(int)(Z); X < z; ++X)
#define fori(X,Y) fora(i,X,Y)
#define forito(X) fora(i,0,X)

#define FILELINE (std::string(__FILE__) + "::" + tos(__LINE__))
#define defer(code)  ScopeExit STRING_JOIN(scope_exit_, __LINE__)([&](){code;});
#define pln(X) std::cout << (X) << std::endl;
#define pnl std::cout << std::endl;
#define del( X ) {if( X ) delete ( X ); ( X ) = nullptr;}
#define delarr( X ) {if( X ) delete [] ( X ); ( X ) = nullptr;}
#define nil nullptr
#define cexpr constexpr
#define self (*this)

const std::string tab("\t");
const std::string nl("\n");
const std::string estr("");
typedef long long int llint;
template<typename T> using sptr = std::shared_ptr<T>;


std::string tos(const std::string& str);
template <typename T> std::string tos(T value) {return to_string(value);}
template <typename T> T lex(const std::string& str) {
	T var;
	std::istringstream iss;
	iss.str(str);
	iss >> var;
	return var;
}


} // namespace tdd





#endif /* HACKS_H_ */
