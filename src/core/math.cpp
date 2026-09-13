#include <include/core/math.h>

sciNo multiply_sciNo(sciNo& a, sciNo& b) {
	sciNo res;
	res.n = a.n * b.n;
	res.exponent = a.exponent + b.exponent;
	return res;
}

sciNo divide_sciNo(sciNo &a, sciNo& b) {
	sciNo res;
	res.n = a.n / b.n;
	res.exponent = a.exponent - b.exponent;
	return res;
}
