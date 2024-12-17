#include "MovePruner.h"

MovePruner::MovePruner()
{
}

// Checks for redundant moves from symmetry, ie. L then R is equivalent to R then L. Returns a vector of variable size as the next moves that should be searched
std::vector<uint8_t> MovePruner::pruneMoves(uint8_t move)
{
	std::vector<uint8_t> moveList;
	for (uint8_t i = 0; i < 18; i++)
	{
		moveList.push_back(i);
	}
	if (move >= 0 && move <= 2)
	{
		moveList.erase(std::next(moveList.begin(), 0), std::next(moveList.begin(), 3));
		moveList.erase(std::next(moveList.begin(), 9), std::next(moveList.begin(), 12));
	}
	else if (move >= 3 && move <= 5)
	{
		moveList.erase(std::next(moveList.begin(), 3), std::next(moveList.begin(), 6));
		moveList.erase(std::next(moveList.begin(), 12), std::next(moveList.begin(), 15));
	}
	else if (move >= 6 && move <= 8)
	{
		moveList.erase(std::next(moveList.begin(), 6), std::next(moveList.begin(), 9));
		moveList.erase(moveList.end() - 3, moveList.end());
	}
	else if (move >= 9 && move <= 11)
	{
		moveList.erase(std::next(moveList.begin(), 9), std::next(moveList.begin(), 12));
	}
	else if (move >= 12 && move <= 14)
	{
		moveList.erase(std::next(moveList.begin(), 12), std::next(moveList.begin(), 15));
	}
	else
	{
		moveList.erase(moveList.end() - 3, moveList.end());
	}
	return moveList;
}
