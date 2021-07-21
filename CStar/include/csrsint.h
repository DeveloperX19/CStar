#ifndef CSTARLIBRARY_SINT
#define CSTARLIBRARY_SINT
#include "csrlib.h"

//using type = ...      -> mask<>::type


//using type = ...      -> sint<>::type

//Unsigned: res = a # b;
//	(res	<	a) -> overflow(+)
//	(b		>	a) -> underflow(-)
//	(res/a	!=	b) -> overflow(*)
//	(b		==	0) -> divzero(/)
//	(b		==	0) -> modzero(%)
//...

//Signed:
//std::make_unsigned -> no UB
//...

//csr::exc::	
//enum class sint { OVERFLOW, UNDERFLOW, DIVZERO, ..., UNSIGNED, ADD, ... }
//throw sint::OVERFLOW | sint::UNSIGNED | sint::ADD;

#endif