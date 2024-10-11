/*
IDA* double ended search with pruning tables to find optimal solution for rubiks cube.
*/
#include <iostream>
#include <array>

#include "./CubeState.h"

using namespace std;

int main()
{
    CubeState cube;

    // Cube State and turning tests
    
    array<string, 25> moves = { "U", "B'", "D2", "U", "B", "U'", "R", "B", "U2", "B2", "F", "R2", "U", "D'", "R2", "B'", "U", "L'", "U2", "D2", "F2", "U2", "L2", "U'", "D" };
    for (string move : moves)
    {
        cube.move(cube._moves[move]);
    }


    cube.display();

    return 0;
}

