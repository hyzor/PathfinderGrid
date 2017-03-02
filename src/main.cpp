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
	std::cout << "Starting grid pathfinding..." << std::endl;

	Pathfinder* pathfinder = new Pathfinder();

	const int bufferSize = 12;

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

	// Example 2
	const unsigned char pMap2[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
	int pOutBuffer2[7];
	output = pathfinder->FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, 7);

	// Assert expected output value
	assert(output == -1);

	// Clean up
	delete pathfinder;

	std::cout << "Pathfinding executed as expected! Press enter to exit." << std::endl;

	std::cin.get();

	// Check for memory leaks
	_CrtDumpMemoryLeaks();
}