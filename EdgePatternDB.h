#pragma once
#include "PatternDB.h"

class EdgePatternDB : public PatternDB
{
public:
	EdgePatternDB(CubeState* Cube);
	int findSmaller(std::array<uint8_t, 12> edges, int start);
	int64_t getIndex(std::array<uint8_t, 12> edges);
	void generateVector();
	std::array<uint8_t, 12> updateEdges(std::array<uint8_t, 12> edgeArray, int move);
};

