/*
A Rubik's cube state class to track current Rubik's Cube position and moves.
Stores each piece (edges and corners serparate) as an integer found by
combining its position (0-7 for corner pieces, 0-11 for edge pieces) with its
orientation (0-2 for corner pices, 0-1 for edge pieces).

This cube state 'renders' the cube with the green face as the 'front' face and
yellow as the 'up' face. The position indeces are as follows:

Edges:
    0  1  2  3  4  5  6  7  8  9  10 11
    UB UR UF UL BL BR FR FL DB DR DF DL

If the edge is 'flipped' it is considered to have an orientation of 1, and 12
is added to its index. ie. if the Green-Red edge piece is correctly positioned,
and correctly oriented, its index would be 7 (FL), but if that same piece were
flipped and in the down-front postion (where Green-White should be), its index
would be 22

Corners:
   0   1   2   3   4   5   6   7
   UBL UBR UFR UFL DBL DBR DFR DFL

Corners have 3 potential orientations (correct, clockwise, and counterclockwise).
If a corner is considered clockwise twisted, 8 will be added to its position
index, and if it is counterclockwise twisted, 16 will be added. ie. if the
White-Blue-Orange corner were correctly positioned and oriented, it would have
index 5. But if it were in the UFL position (normally Yellow-Green-Red), and
twisted clockwise, its index would be 11.
*/

#ifndef CubeState_HEADER
#define CubeState_HEADER

#pragma once

#include <array>
#include <string>
#include <map>
#include <list>
#include <cstdint>

class CubeState
{
public:
    // Arrays to store edge piece and corner piece indeces.
    std::array<uint8_t, 12> _edges;
    std::array<uint8_t, 8> _corners;

    std::map<uint8_t, std::string> _moves = {
        {0, "U"},
        {1, "U2"},
        {2, "U'"},
        {3, "R"},
        {4, "R2"},
        {5, "R'"},
        {6, "F"},
        {7, "F2"},
        {8, "F'"},
        {9, "D"},
        {10, "D2"},
        {11, "D'"},
        {12, "L"},
        {13, "L2"},
        {14, "L'"},
        {15, "B"},
        {16, "B2"},
        {17, "B'"}
    };

    std::map<std::string, uint8_t> _movesToInt = {
        {"U", 0},
        {"U2", 1},
        {"U'", 2},
        {"R", 3},
        {"R2", 4},
        {"R'", 5},
        {"F", 6},
        {"F2", 7},
        {"F'", 8},
        {"D", 9},
        {"D2", 10},
        {"D'", 11},
        {"L", 12},
        {"L2", 13},
        {"L'", 14},
        {"B", 15},
        {"B2", 16},
        {"B'", 17}
    };

    std::map<uint8_t, std::string> _cornerIndexToColors = {
        {0, "YBR"},
        {1, "YBO"},
        {2, "YGO"},
        {3, "YGR"},
        {4, "WBR"},
        {5, "WBO"},
        {6, "WGO"},
        {7, "WGR"}
    };

    std::map<uint8_t, std::string> _edgeIndexToColors = {
        {0, "YB"},
        {1, "YO"},
        {2, "YG"},
        {3, "YR"},
        {4, "BR"},
        {5, "BO"},
        {6, "GO"},
        {7, "GR"},
        {8, "WB"},
        {9, "WO"},
        {10, "WG"},
        {11, "WR"}
    };

    std::map<std::string, uint8_t> _cornerColorsToIndex = {
        {"YBR", 0},
        {"YBO", 1},
        {"YGO", 2},
        {"YGR", 3},
        {"WBR", 4},
        {"WBO", 5},
        {"WGO", 6},
        {"WGR", 7}
    };

    std::map<std::string, uint8_t> _edgeColorsToIndex = {
        {"YB", 0},
        {"YO", 1},
        {"YG", 2},
        {"YR", 3},
        {"BR", 4},
        {"BO", 5},
        {"GO", 6},
        {"GR", 7},
        {"WB", 8},
        {"WO", 9},
        {"WG", 10},
        {"WR", 11}
    };

    CubeState();
    CubeState(std::array<uint8_t, 12> edge, std::array<uint8_t, 8> corner);


    std::array<uint8_t, 12> getEdges();
    std::array<uint8_t, 8> getCorners();
    uint8_t flip(uint8_t edgeInd);
    uint8_t clockwise(uint8_t cornerInd);
    uint8_t counterClockwise(uint8_t cornerInd);

    bool solvedState();

    void displayArrays();
    void displayColors();

    CubeState& move(int move);

    CubeState& u();
    CubeState& u2();
    CubeState& u3();

    CubeState& r();
    CubeState& r2();
    CubeState& r3();

    CubeState& f();
    CubeState& f2();
    CubeState& f3();

    CubeState& d();
    CubeState& d2();
    CubeState& d3();

    CubeState& l();
    CubeState& l2();
    CubeState& l3();

    CubeState& b();
    CubeState& b2();
    CubeState& b3();

};

#endif 