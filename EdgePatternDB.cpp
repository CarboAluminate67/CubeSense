#include "EdgePatternDB.h"

EdgePatternDB::EdgePatternDB(CubeState* pcube)
{
	Cube = pcube;
}

// Part of indexing, finds the number of smaller numbers following position 'start'
int EdgePatternDB::findSmaller(std::array<uint8_t, 12> edges, int start)
{
	int count = 0;
	for (int i = start + 1; i < 12; i++)
	{
		if (edges[start] > edges[i])
		{
			++count;
		}
	}
	return count;
}

int64_t EdgePatternDB::getIndex(std::array<uint8_t, 12> edges)
{
	// Edge Pattern DB only uses permutation otherwise it would be too large
	std::array<uint8_t, 12> edgePerms;

	for (int i = 0; i < 12; i++)
	{
		edgePerms[i] = edges[i] % 12;
	}

	// Rank(index) is the number of permutations that come before the current one lexicographically
	int64_t rank = 0;

	for (int i = 0; i < 12; ++i)
	{
		rank += findSmaller(edgePerms, i) * fact(11 - i);
	}

	return rank;
}

void EdgePatternDB::generateVector()
{
	MovePruner movePruner;
	// ~480000000 possible edge permutations
	std::vector<uint8_t> edges(479001600, 8);
	std::queue<std::tuple<std::array<uint8_t, 12>, uint8_t, uint8_t>> q;

	std::array<uint8_t, 12> edgeArray;

	uint8_t depth = 0;
	uint8_t move = 0;

	int64_t ind = 0;

	edges[ind] = depth;

	for (uint8_t i = 0; i < 18; i++)
	{
		q.push({ Cube->getEdges(), i, 1 });
	}

	// Breadth First Traversal recording current depth to update edge pattern DBs
	while (!q.empty())
	{
		edgeArray = std::get<0>(q.front());
		move = std::get<1>(q.front());
		depth = std::get<2>(q.front());
		q.pop();

		edgeArray = this->updateEdges(edgeArray, move);
		ind = this->getIndex(edgeArray);
		if (edges[ind] > depth)
		{
			if (depth < 7)
			{
				for (uint8_t num : movePruner.pruneMoves(move))
				{
					q.push({ edgeArray, num, depth + 1 });
				}
			}
			edges[ind] = depth;
		}
	}

	this->saveVector("EdgePatternDatabase.bin", edges);
}

// Helper function to independantly update edge array from a move
std::array<uint8_t, 12> EdgePatternDB::updateEdges(std::array<uint8_t, 12> edgeArray, int move)
{
	CubeState edgeCube(edgeArray, {0, 1, 2, 3, 4, 5, 6, 7});

	edgeCube.move(move);
	return edgeCube.getEdges();
}