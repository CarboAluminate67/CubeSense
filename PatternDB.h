#pragma once
#include "CubeState.h"
#include <array>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <queue>
#include <unordered_map>
#include "MovePruner.h"

class PatternDB
{
protected:
	CubeState* Cube;
public:
	std::vector<uint8_t> _vector;
	int fact(int n);
	void saveVector(const char* fileName);
	void saveVector(const char* fileName, std::vector<uint8_t> vect);
	void loadVector(const char* fileName);
};

