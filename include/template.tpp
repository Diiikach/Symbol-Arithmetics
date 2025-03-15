#include "expression.hpp"
#include "../src/expression.cpp"
#include "../src/add.cpp"
#include "../src/cos.cpp"
#include "../src/div.cpp"
#include "../src/exp.cpp"
#include "../src/ln.cpp"
#include "../src/mul.cpp"
#include "../src/pow.cpp"
#include "../src/sin.cpp"
#include "../src/unary_minus.cpp"
#include "../src/value.cpp"
#include "../src/variable.cpp"


template class Expression<long double>;
template class Expression<int>;
