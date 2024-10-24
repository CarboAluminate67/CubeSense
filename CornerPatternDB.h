#include "CubeState.h"
#include <array>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

class CornerPatternDB
{
private:
	CubeState* Cube;

public:
	CornerPatternDB(CubeState* Cube);
	int fact(int n);
	int findSmaller(std::array<uint8_t, 8> corners, int start);
	double getIndex();
	void saveVector(std::string fileName, std::vector<uint8_t> cornerVector);
};

