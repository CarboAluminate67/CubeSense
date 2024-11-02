/*
IDA* double ended search with pruning tables to find optimal solution for rubiks cube.
*/
#include <iostream>
#include <array>
#include <vector>

#include "./CubeState.h"
#include "./CornerPatternDB.h"

using namespace std;

int main()
{

    CubeState cube;
    CornerPatternDB cornerDB(&cube);

    // Testing

    cube.u();
    cube.r();
    cube.b3();
    cube.l();
    cube.d2();

    cube.display();

    cout << endl << setprecision(10) << cornerDB.getIndex(cube.getCorners());

    cornerDB.generateVector();

    cornerDB.loadVector("CornerPatternDatabase.bin");


    cout << endl << cornerDB.cornerVector[4337539];

    return 0;
}

