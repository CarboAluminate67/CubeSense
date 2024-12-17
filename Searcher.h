#pragma once

#include "CubeState.h"
#include <vector>
#include <stack>
#include "CornerPatternDB.h"
#include "EdgePatternDB.h"
#include "MovePruner.h"
#include <array>

class Searcher
{
private:
	EdgePatternDB edgeDB;
	CornerPatternDB cornerDB;
public:
	Searcher(EdgePatternDB* pedgeDB, CornerPatternDB* pcornerDB);
	std::array<uint8_t, 30> findSolution(CubeState _cube, bool intermediate);
	uint8_t heuristic(CubeState cube);
	void displaySolution(std::array<uint8_t, 30> sol, CubeState cube);
};

