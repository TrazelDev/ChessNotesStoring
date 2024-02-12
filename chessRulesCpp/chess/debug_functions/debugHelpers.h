#pragma once
#include <bitset>
#define NUM_OF_PIECES 15

namespace debug
{
	void printArrs(std::bitset<NUM_OF_PIECES>** arr);
	void resetArr(std::bitset<NUM_OF_PIECES>** arr);
	void printaArrIndex(std::bitset<NUM_OF_PIECES>** arr, const int& index);
}
