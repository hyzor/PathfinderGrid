//==========================================================
// A* pathfinding solution for Paradox Interactive
// Author: Jesper Hansson Falkenby
// Date: 2017-03-03
//==========================================================

#include <iostream>
#include <assert.h>
#include "Util.h"
#include "Pathfinder.h"

// Enable memory leak checking
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 

int main(int argc, char** argv)
{
	std::cout << "Starting grid pathfinding..." << std::endl << std::endl;

	Pathfinder* pathfinder = new Pathfinder();

	const int bufferSize = 12;
	const int bufferSize2 = 12;

	std::cout << "Executing first example..." << std::endl;

	// Example 1
	const unsigned char pMap[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	int pOutBuffer[bufferSize];
	int output = -1;
	output = pathfinder->FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

	// Assert expected output value
	assert(output == 3);

	// Assert expected output array
	const int expected[] = { 1, 5, 9 };
	bool arrayIsValid = Util::VerifyArray(pOutBuffer, expected);
	assert(arrayIsValid == true);

	for (int i = 0; i < output - 1; ++i)
	{
		std::cout << pOutBuffer[i] << ", ";
	}

	std::cout << pOutBuffer[output - 1] << std::endl << std::endl;

	std::cout << "Executing second example..." << std::endl;

	// Example 2
	const unsigned char pMap2[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
	int pOutBuffer2[bufferSize2];
	output = pathfinder->FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, bufferSize2);

	// Assert expected output value
	assert(output == -1);

	std::cout << std::endl;

	// Clean up
	delete pathfinder;

	std::cout << "Pathfinding examples executed as expected! Press enter to exit." << std::endl;

	std::cin.get();

	// Check for memory leaks
	_CrtDumpMemoryLeaks();
}