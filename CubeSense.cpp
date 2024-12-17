/*
IDA* double ended search with pruning tables to find optimal solution for rubiks cube.
*/

#include <iostream>
#include <array>
#include <vector>
#include <sstream>
#include <filesystem>

#include "./CubeState.h"
#include "./CornerPatternDB.h"
#include "./EdgePatternDB.h"
#include "./Searcher.h"

#include <chrono>

using namespace std;

int main()
{
    // Initializing objects/variables 
    CubeState cube;

    CornerPatternDB cornerDB(&cube);
    EdgePatternDB edgeDB(&cube);

    int choice = 0;
    string Scramble;
    vector<string> ScrambleMoves;

    string CornerColors;
    string EdgeColors;
    vector<string> CornerColorPieces;
    vector<string> EdgeColorPieces;

    string delim = " ";
    string piece;

    // Basic menu CLI system
    cout << "Welcome to CubeSense Rubik's Cube Solver\n";
    while (choice != 8)
    {
        cout << "\nOptions: \n";
        cout << "1. Enter Scramble\n";
        cout << "2. Enter Cube\n";
        cout << "3. View Cube\n";
        cout << "4. View Cube Arrays\n";
        cout << "5. Solve Cube\n";
        cout << "6. Load Pattern Databases\n";
        cout << "7. Generate Pattern Databases\n";
        cout << "8. Quit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                // Vector stores individual moves
                ScrambleMoves.clear();
                cout << "Enter Scramble: ";
                getline(cin >> ws, Scramble);

                stringstream ss(Scramble);

                while (getline(ss, piece, delim[0]))
                {
                    ScrambleMoves.push_back(piece);
                }

                // Applies moves to cube object
                for (const auto& t : ScrambleMoves) 
                {
                    cube.move(cube._movesToInt[t]);
                }
                break;
            }

            case 2:
            {
                // Individual vectors for corner and edge colors
                cout << "Enter Corner Colors: ";
                getline(cin >> ws, CornerColors);
                cout << "Enter Edge Colors: ";
                getline(cin >> ws, EdgeColors);

                stringstream corner_ss(CornerColors);
                stringstream edge_ss(EdgeColors);

                while (getline(corner_ss, piece, delim[0]))
                {
                    CornerColorPieces.push_back(piece);
                }

                while (getline(edge_ss, piece, delim[0]))
                {
                    EdgeColorPieces.push_back(piece);
                }

                // Converts colors to indeces and sets the cube arrays accordingly
                for (int i = 0; i < 8; i++)
                {
                    cube._corners[i] = cube._cornerColorsToIndex[CornerColorPieces[i].substr(0, 3)];
                    cube._corners[i] += 8 * (CornerColorPieces[i].back() - '0');
                }

                cout << endl;

                for (int i = 0; i < 12; i++)
                {
                    cube._edges[i] = unsigned(cube._edgeColorsToIndex[EdgeColorPieces[i].substr(0, 2)]);
                    
                    cube._edges[i] += 12 * (EdgeColorPieces[i].back() - '0');
                }

                // TESTING PURPOSES //

                // D' B' D F B' U F2 U2 B R2 U2 R2 F D2 R2 L2 B'

                // YBR-0 YGO-1 WGO-2 YGR-0 WBR-0 YBO-2 WBO-1 WGR-0
                // YB-0 GO-1 YG-0 YR-0 BR-0 YO-1 WO-1 GR-0 WB-0 BO-1 WG-0 WR-0
                
                break;
            }

            case 3:
            {
                // Displays cube in color notation
                cube.displayColors();
                break;
            }

            case 4:
            {
                // Displays cube in form of piece arrays
                cube.displayArrays();
                break;
            }

            case 5:
            {
                // Searcher object
                Searcher searcher(&edgeDB, &cornerDB);

                // Time tracking
                auto start = chrono::high_resolution_clock::now();

                // Call to begin sarch algorithm
                array<uint8_t, 30> solution = searcher.findSolution(cube, false);
                searcher.displaySolution(solution, cube);

                auto stop = chrono::high_resolution_clock::now();

                auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                cout << endl << "Time to find solution: " << duration.count() / 1000000 << " seconds" << endl;

                break;
            }

            case 6:
            {
                // Loads ~1 GB of pattern DBs into memory
                edgeDB.loadVector("EdgePatternDatabase.bin");
                cornerDB.loadVector("CornerPatternDatabase.bin");

                cout << "Databases loaded";

                break;
            }

            case 7:
            {
                // Manually re-generates pattern DBs, can take ~2 hours
                cornerDB.generateVector();
                edgeDB.generateVector();

                break;
            }

            default:
            {
                cout << "Invalid Choice.";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
        }
    }

    return 0;
}

