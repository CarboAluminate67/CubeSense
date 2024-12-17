#pragma once
#include <array>
#include <vector>

class MovePruner
{
public:
	MovePruner();
	std::vector<uint8_t> pruneMoves(uint8_t move);
};

