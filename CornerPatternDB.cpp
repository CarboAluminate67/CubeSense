#include "CornerPatternDB.h"


CornerPatternDB::CornerPatternDB(CubeState* pcube)
{
	Cube = pcube;
}

// Part of indexing, finds the number of smaller numbers following position 'start'
int CornerPatternDB::findSmaller(std::array<uint8_t, 8> corners, int start)
{
	int count = 0;
	for (int i = start + 1; i < 8; i++)
	{
		if (corners[start] > corners[i])
		{
			++count;
		}
	}
	return count;
}


int64_t CornerPatternDB::getIndex(std::array<uint8_t, 8> corners)
{
	std::array<uint8_t, 8> cornerPerms;
	std::array<uint8_t, 7> cornerOrien;

	// Converts corner array into 2 separate arrays (one for permutation, one for orientation)
	for (int i = 0; i < 8; i++)
	{
		cornerPerms[i] = corners[i] % 8;
		if (i != 7)
		{
			cornerOrien[i] = floor(corners[i] / 8);
		}
	}


	int64_t rank = 0;

	// Rank(index) is the number of permutations that come before the current one lexicographically
	for (int i = 0; i < 8; ++i)
	{
		rank += findSmaller(cornerPerms, i) * fact(7 - i);
	}


	rank *= 2187;
	for (int i = 0; i < 7; i++)
	{
		rank += cornerOrien[i] * pow(3, 6 - i);
	}
	return rank;
}

void CornerPatternDB::generateVector()
{
	MovePruner movePruner;
	
	// ~88000000 possible corner states to be searched
	std::vector<uint8_t> corners(88179840, 10);
	std::queue<std::tuple<std::array<uint8_t, 8>, uint8_t, uint8_t>> q;

	std::array<uint8_t, 8> cornerArray;
	
	uint8_t depth = 0;
	uint8_t move = 0;

	int64_t ind = 0;
	
	corners[ind] = depth;

	// Breadth First Traversal recording current depth to update corner pattern DBs
	for (uint8_t i = 0; i < 18; i++)
	{
		q.push({ Cube->getCorners(), i, 1 });
	}

	while (!q.empty())
	{
		cornerArray = std::get<0>(q.front());
		move = std::get<1>(q.front());
		depth = std::get<2>(q.front());
		q.pop();

		cornerArray = this->updateCorners(cornerArray, move);
		ind = this->getIndex(cornerArray);
		if (corners[ind] > depth)
		{
			if (depth < 9)
			{
				for (uint8_t num : movePruner.pruneMoves(move))
				{
					q.push({ cornerArray, num, depth + 1 });
				}
			}
			uint8_t temp = corners[ind];
			corners[ind] = depth;
		}
	}

	this->saveVector("CornerPatternDatabase.bin", corners);
}

// Helper function to update corner array independantly based on a move
std::array<uint8_t, 8> CornerPatternDB::updateCorners(std::array<uint8_t, 8> cornerArray, int move)
{
	CubeState cornerCube({ 0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11 }, cornerArray);

	cornerCube.move(move);
	return cornerCube.getCorners();
}
