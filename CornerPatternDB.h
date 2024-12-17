#pragma once
#include "PatternDB.h"

class CornerPatternDB : public PatternDB
{
public:
	CornerPatternDB(CubeState* Cube);
	int findSmaller(std::array<uint8_t, 8> corners, int start);
	int64_t getIndex(std::array<uint8_t, 8> corners);
	void generateVector();
	std::array<uint8_t, 8> updateCorners(std::array<uint8_t, 8> cornerArray, int move);
};

