//==========================================================
// A* pathfinding solution for Paradox Interactive
// Author: Jesper Hansson Falkenby
// Date: 2017-03-03
//==========================================================

#include <iostream>
#include <assert.h>
#include <thread>
#include <future>
#include "Util.h"
#include "Pathfinder.h"

int main(int argc, char** argv)
{
	std::cout << "Starting grid pathfinding..." << std::endl << std::endl;

	std::thread threads[3];

	const int bufferSize = 12;
	const int bufferSize2 = 12;
	const int bufferSize3 = 12;

	bool useThreads = false;

	std::cout << "Executing first example..." << std::endl;

	// Thread buffers
	const unsigned char pMap[] = {	1, 1, 1, 1,
									0, 1, 0, 1,
									0, 1, 1, 1 };
	int pOutBuffer[bufferSize];
	int output = -1;

	const unsigned char pMap2[] = { 1, 1, 1,
		0, 0, 1,
		0, 1, 1 };
	int pOutBuffer2[bufferSize2];

	const unsigned char pMap3[] = { 0, 0, 1,
		0, 1, 1,
		1, 0, 1 };
	int pOutBuffer3[bufferSize3];

	if (useThreads)
	{
		threads[0] = std::thread(&FindPath, 0, 0, 1, 2, pMap, 4, 3, pOutBuffer, bufferSize);
		threads[1] = std::thread(&FindPath, 0, 0, 2, 2, pMap2, 3, 3, pOutBuffer2, bufferSize2);
		threads[2] = std::thread(&FindPath, 2, 0, 0, 2, pMap3, 3, 3, pOutBuffer3, bufferSize3);

		threads[0].join();
		threads[1].join();
		threads[2].join();

		for (int i = 0; i < bufferSize; ++i)
		{
			std::cout << pOutBuffer[i] << ", ";
		}

		std::cout << std::endl;

		for (int i = 0; i < bufferSize2; ++i)
		{
			std::cout << pOutBuffer2[i] << ", ";
		}

		std::cout << std::endl;

		for (int i = 0; i < bufferSize3; ++i)
		{
			std::cout << pOutBuffer3[i] << ", ";
		}

		std::cout << std::endl;
	}
	else
	{
		// Example 1
		output = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

		// Assert expected output value
		assert(output == 3);

		// Verify the correctness of our pathfinder
		const int expectedOut[] = { 1, 5, 9 };
		const int expectedOutSize = sizeof(expectedOut) / sizeof(expectedOut[0]);

		// Assert that output is at least as big as the expected array
		assert(bufferSize >= expectedOutSize && output >= expectedOutSize);

		// Now assert that the path is equal to our verification path
		bool arrayIsValid = Util::VerifyArray(pOutBuffer, expectedOut, output);
		assert(arrayIsValid == true);

		for (int i = 0; i < output - 1; ++i)
		{
			std::cout << pOutBuffer[i] << ", ";
		}

		std::cout << pOutBuffer[output - 1] << std::endl << std::endl;

		std::cout << "Executing second example..." << std::endl;

		// Example 2
		output = FindPath(2, 0, 0, 2, pMap3, 3, 3, pOutBuffer3, bufferSize3);

		// Assert expected output value
		assert(output == -1);

		std::cout << std::endl;
	}

	std::cout << "Pathfinding examples executed as expected! Press enter to exit." << std::endl;

	std::cin.get();
}