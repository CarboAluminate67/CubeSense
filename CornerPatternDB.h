#include "CubeState.h"
#include <array>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>
typedef uint8_t BYTE;
#include <iomanip>
#include <queue>
#include <unordered_map>

class CornerPatternDB
{
private:
	CubeState* Cube;
public:
	std::vector<uint8_t> cornerVector;
	CornerPatternDB(CubeState* Cube);
	int fact(int n);
	int findSmaller(std::array<uint8_t, 8> corners, int start);
	double getIndex(std::array<uint8_t, 8> corners);
	void saveVector(const char* fileName);
	void saveVector(const char* fileName, std::vector<uint8_t> vect);
	void loadVector(const char* fileName);
	void generateVector();
	std::array<uint8_t, 8> updateCorners(std::array<uint8_t, 8> cornerArray, int move);
};

