#include "PatternDB.h"

// Basic factorial 
int PatternDB::fact(int n)
{
	int f = 1;
	for (int i = 2; i <= n; i++)
	{
		f *= i;
	}
	return f;
}

// Saves anonymous vector to a binary file
void PatternDB::saveVector(const char* fileName)
{
	remove(fileName);
	const std::vector<uint8_t>  buffer(_vector);
	std::ofstream outFile(fileName, std::ios::out | std::ios::binary);
	outFile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
	outFile.close();
}

// Saves specified vector to a binary file
void PatternDB::saveVector(const char* fileName, std::vector<uint8_t> vect)
{
	remove(fileName);
	const std::vector<uint8_t>  buffer(vect);
	std::ofstream outFile(fileName, std::ios::out | std::ios::binary);
	outFile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
	outFile.close();
}

// Reads binary file into a vector kept in memory during search
void PatternDB::loadVector(const char* fileName)
{
	std::ifstream instream(fileName, std::ios::in | std::ios::binary);
	std::vector<uint8_t> data((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());
	_vector = data;
}