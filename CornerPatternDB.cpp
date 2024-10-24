#include "CornerPatternDB.h"

CornerPatternDB::CornerPatternDB(CubeState* Cube) : Cube(Cube)
{
}

int CornerPatternDB::fact(int n)
{
	int f = 1;
	for (int i = 2; i < n; i++)
	{
		f *= i;
	}
	return f;
}

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

double CornerPatternDB::getIndex()
{
	std::array<uint8_t, 8> corners = Cube->getCorners();
	std::array<uint8_t, 8> cornerPerms;
	std::array<uint8_t, 7> cornerOrien;

	for (int i = 0; i < 8; i++)
	{
		cornerPerms[i] = corners[i] % 8;
		if (i != 7)
		{
			cornerOrien[i] = floor(corners[i] / 8);
		}
	}


	double rank = 0;

	for (int i = 0; i < 8; ++i)
	{
		rank += findSmaller(cornerPerms, i) * fact(8 - i);
		std::cout << "\nPerm Rank: " << rank;
	}


	rank *= 2187;
	for (int i = 0; i < 7; i++)
	{
		rank += cornerOrien[i] * pow(3, 6 - i);
	}
	return rank;
}

void CornerPatternDB::saveVector(std::string fileName, std::vector<uint8_t> cornerVector)
{
	std::ofstream out(fileName, std::ios_base::binary);
	uint64_t size = cornerVector.size();
	out.write(reinterpret_cast<char*>(&size), sizeof(size));
	out.write(reinterpret_cast<char*>(cornerVector.data()), size * sizeof(int));
}
