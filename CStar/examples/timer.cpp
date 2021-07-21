#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "../include/csrlib.h"
#include "../include/csrtimer.h"

//bubble sort implementation
void garbageSort(int* arr, size_t len)
{
	len--;
	for (size_t i = 0; i < len; i++)
		for (size_t j = 0; j < len - i; j++)
			if (arr[j] > arr[j + 1])
				std::swap(arr[j], arr[j + 1]);
}

int main()
{
	std::cout << ">--  C-Star Timer  --<" << std::endl;

	constexpr size_t arrLen = 5000;
	csr::tool::Timer<csr::args::TTS::ms> watch;

	int* data = new int[arrLen];

	//fill array with random data
	for (size_t i = 0; i < arrLen; i++)
		data[i] = rand();

	//measure time of bubble sort
	watch.resume();
	garbageSort(data, arrLen);
	watch.pause();
	std::cout << "Bubble Sort finished in " << watch.getTime() << " ms." << std::endl;
	watch.reset();

	//fill array with random data
	for (size_t i = 0; i < arrLen; i++)
		data[i] = rand();

	//measure time of std::sort
	watch.resume();
	std::sort(data, data + arrLen, [](const int& a, const int& b) { return a < b; });
	watch.pause();
	std::cout << "std::sort finished in " << watch.getTime() << " ms." << std::endl;
	watch.reset();

	delete[] data;

	//prime the clock
	watch.clock();
	watch.resume();
	for (int i = 0; i < 10; i++)
	{
		//wait until another iteration should start
		watch.clock(500);
		//verify iteration delay
		std::cout << "iteration " << i+1 << " occured after " << watch.getTime() << " ms." << std::endl;
		watch.reset();
		watch.resume();

		//simulate work with varying time cost 
		unsigned int rdmTime = (unsigned)(rand()) % 450;
		watch.wait(rdmTime);
	}

	std::cout << "<--  C-Star Timer  -->" << std::endl;
	return 0;
}

/*
Output :

	>--  C-Star Timer  --<
	Bubble Sort finished in 302 ms.
	std::sort finished in 3 ms.
	iteration 1 occured after 500 ms.
	iteration 2 occured after 499 ms.
	iteration 3 occured after 499 ms.
	iteration 4 occured after 499 ms.
	iteration 5 occured after 500 ms.
	iteration 6 occured after 499 ms.
	iteration 7 occured after 499 ms.
	iteration 8 occured after 499 ms.
	iteration 9 occured after 499 ms.
	iteration 10 occured after 499 ms.
	<--  C-Star Timer  -->

*/