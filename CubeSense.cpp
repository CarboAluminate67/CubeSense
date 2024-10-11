/*
IDA* double ended search with pruning tables to find optimal solution for rubiks cube.
*/
#include <iostream>

#include "./CubeState.h"

using namespace std;

int main()
{
    CubeState cube;
    array<uint8_t, 12> edges;
    array<uint8_t, 8> corners;
    edges = cube.getEdges();
    corners = cube.getCorners();

    cout << "Edge array: \n";
    for (unsigned i = 0; i < 12; i++)
    {
        cout << edges[i] << " ";
    }

    cout << "\n Corner array: \n";
    for (unsigned i = 0; i < 8; i++)
    {
        cout << corners[i] << " ";
    }


    return 0;
}

