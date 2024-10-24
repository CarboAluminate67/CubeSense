/*
IDA* double ended search with pruning tables to find optimal solution for rubiks cube.
*/
#include <iostream>
#include <array>

#include "./CubeState.h"
#include "./CornerPatternDB.h"

using namespace std;

int main()
{
    CubeState cube;

    // Testing
    
    CornerPatternDB cornerDB(&cube);

    cube.display();

    cube.r();

    cout << "\n\n" << cornerDB.getIndex();

    return 0;
}

