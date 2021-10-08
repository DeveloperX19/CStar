#ifndef CSTARLIBRARY_SINT
#define CSTARLIBRARY_SINT

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




/*
int safe_int_div(int * res, int op1, int op2) {
  if (op2 == 0) {
    return 1;
  }
  // 2's complement detection
  #if (INT_MIN != -INT_MAX)
    if (op1 == INT_MIN && op2 == -1)  {
      return 1;
    }
  #endif
  *res = op1 / op2;
  return 0;
}
*/

#endif