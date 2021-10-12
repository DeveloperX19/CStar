#include <iostream>
#include "../csrlib.h"
#include "csrmask.h"

enum class Bitflags
{
	A,
	B
};

int main()
{
	std::cout << ">--  C-Star Mask  --<" << std::endl;
	cstar::mask<Bitflags> m;
	std::cout << m << std::endl;
	std::cout << m.capacity() << std::endl;

	std::cout << "<--  C-Star Mask  -->" << std::endl;
	return 0;
}

/*
Output :

	>--  C-Star Mask  --<
	<--  C-Star Mask  -->

*/