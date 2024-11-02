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

double CornerPatternDB::getIndex(std::array<uint8_t, 8> corners)
{
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
	}


	rank *= 2187;
	for (int i = 0; i < 7; i++)
	{
		rank += cornerOrien[i] * pow(3, 6 - i);
	}
	return rank;
}

void CornerPatternDB::saveVector(const char* fileName)
{
	remove(fileName);
	const std::vector<uint8_t>  buffer(cornerVector);
	std::ofstream outFile(fileName, std::ios::out | std::ios::binary);
	outFile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
	outFile.close();
}

void CornerPatternDB::saveVector(const char* fileName, std::vector<uint8_t> vect)
{
	remove(fileName);
	const std::vector<uint8_t>  buffer(vect);
	std::ofstream outFile(fileName, std::ios::out | std::ios::binary);
	outFile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
	outFile.close();
}

void CornerPatternDB::loadVector(const char* fileName)
{
	std::ifstream instream(fileName, std::ios::in | std::ios::binary);
	std::vector<uint8_t> data((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());
	cornerVector = data;
}

void CornerPatternDB::generateVector()
{
	//std::vector<uint8_t> testing{ 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	std::vector<uint8_t> corners(88179840, 11);
	std::queue<std::tuple<std::array<uint8_t, 8>, int, int>> q;

	std::array<uint8_t, 8> cornerArray;
	
	int depth = 0;

	double ind = 0;
	
	corners[ind] = depth;

	std::array<int, 18> moveList;
	for (int i = 0; i < 18; i++)
	{
		moveList[i] = i;
	}

	for (int num : moveList)
	{
		q.push({ Cube->getCorners(), num, 1});
	}


	while (!q.empty())
	{
		cornerArray = std::get<0>(q.front());
		int move = std::get<1>(q.front());
		depth = std::get<2>(q.front());
		q.pop();

		cornerArray = this->updateCorners(cornerArray, move);

		if (depth < 8)
		{
			for (int num : moveList)
			{
				q.push({ cornerArray, num, depth + 1 });
			}
		}

		ind = this->getIndex(cornerArray);

		if (corners[ind] > depth) 
		{ 
			corners[ind] = depth; 
			//DEBUG_LOG std::cout << std::endl << std::setprecision(10) << "Index # " << ind << "set to " << depth;
		}


	}

	//TEST std::cout << std::endl << std::setprecision(10) << corners[35757862];

	this->saveVector("CornerPatternDatabase.bin", corners);
}

std::array<uint8_t, 8> CornerPatternDB::updateCorners(std::array<uint8_t, 8> cornerArray, int move)
{
	CubeState cornerCube({ 0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11 }, cornerArray);

	cornerCube.move(move);
	return cornerCube.getCorners();
}
