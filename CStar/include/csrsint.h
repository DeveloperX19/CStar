#ifndef CSTARLIBRARY_SINT
#define CSTARLIBRARY_SINT
	#ifndef CSTARLIBRARY
	static_assert(false, "#include 'csrlib.h'");
	#else

//using type = ...      -> mask<>::type


//using type = ...      -> sint<>::type

//Unsigned: res = a # b;
//	(res	<	a) -> overflow(+)
//	(b		>	a) -> underflow(-)
//	(res/a	!=	b) -> overflow(*)	// assert a != 0 (div 0)
//	(b		==	0) -> divzero(/)
//	(b		==	0) -> modzero(%)
//...

//Signed:
//std::make_unsigned -> no UB
//...

//csr::exc::	
//enum class sint { OVERFLOW, UNDERFLOW, DIVZERO, ..., UNSIGNED, ADD, ... }
//throw sint::OVERFLOW | sint::UNSIGNED | sint::ADD;




/*
int safe_int_div(int * res, int op1, int op2) {
	if (op2 == 0) {
	return 1;
	}
	if (op1 == consteval(std::numeric_limits<T>::min()) && op2 == -1)  {
	  return 1;
	}
	*res = op1 / op2;
	return 0;
}
*/

	#endif
#endif