#include "Searcher.h"

Searcher::Searcher(EdgePatternDB* pedgeDB, CornerPatternDB* pcornerDB) : edgeDB(*pedgeDB), cornerDB(*pcornerDB)
{
}

// Returns the max of the two lookup values from pattern DBs, creating an admissable heuristic for the search
uint8_t Searcher::heuristic(CubeState cube)
{
	int64_t edgeIndex = edgeDB.getIndex(cube.getEdges());
	int64_t cornerIndex = cornerDB.getIndex(cube.getCorners());

	uint8_t edgeEstimate = edgeDB._vector[edgeIndex];
	uint8_t cornerEstimate = cornerDB._vector[cornerIndex];

	return std::max(edgeEstimate, cornerEstimate);
}

// Prints the found solution
void Searcher::displaySolution(std::array<uint8_t, 30> sol, CubeState cube)
{
	for (uint8_t i : sol)
	{
		if (i == 0xFF)
		{
			break;
		}
		std::cout << cube._moves[i] << " ";
	}
	std::cout << std::endl;
}

std::array<uint8_t, 30> Searcher::findSolution(CubeState _cube, bool intermediate=false)
{
	// Initializing solution arrays and objects
	std::array<uint8_t, 30> _solution = { 0xFF };
	std::array<uint8_t, 30> interSolution = { 0xFF };
	MovePruner movePruner;

	std::vector<uint8_t> moveList = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };

	CubeState cube;
	uint8_t move;
	uint8_t depth;
	// Stack containing nodes which are tuples of cubes, last move taken to get to it, and depth
	std::stack<std::tuple<CubeState, uint8_t, uint8_t>> stack;
	std::tuple<CubeState, uint8_t, uint8_t> current;

	bool solved = false;
	bool checked;

	// Bounds to guide searcher in how far it expects to search (how far it should search before restarting at a new bound)
	uint8_t estimate = heuristic(_cube);
	uint8_t nextEstimate = heuristic(_cube);

	while (!solved)
	{
		// First iteration, or current estimate is run-out, restarts at root node and updates the estimates
		if (stack.empty())
		{

			stack.push({ _cube, 0xFF, 0 });

			estimate = nextEstimate;
			nextEstimate = 0xFF;
		}

		// Breaks off intermediate solutions, if the solution is not within 5 moves
		if (intermediate && estimate > 6)
		{
			return { 100 };
		}

		// Sets current variables
		current = stack.top();
		stack.pop();

		cube = std::get<0>(current);
		move = std::get<1>(current);
		depth = std::get<2>(current);
		
		// Updates solution array, and checks if cube is solved
		if (depth != 0)
		{
			_solution[depth - 1] = move;
		}
		_solution[depth] = 0xFF;

		if (depth == estimate)
		{
			if (cube.solvedState())
			{
				solved = true;
			}
		}

		// If cube is not solved, it adds a new chain of moves, sorted in a priority queue based on their estimated distance to solution 
		else
		{
			struct priMove
			{
				CubeState cube;
				uint8_t move;
				uint8_t est;
				bool operator<(const priMove& rhs) const
				{
					return this->est < rhs.est;
				}
			};

			std::priority_queue<priMove> leaves;                                                                                                                                                
			// All 18 moves will be searched from root node, otherwise only non-redundant moves
			if (depth != 0)
			{
				moveList = movePruner.pruneMoves(move);
			}

			// Intermediate solution flag
			checked = false;

			for (uint8_t i : moveList)
			{
				CubeState cubeCpy(cube.getEdges(), cube.getCorners());
				// If the heuristic guesses there is a very close solution, exit the current search and make a quick smaller search to find it. 
				if (heuristic(cubeCpy) < 4 && !intermediate && !checked)
				{
					interSolution = findSolution(cubeCpy, true);
					// Small solution was found, search ended
					if (interSolution[0] != 100)
					{
						solved = true;
						break;
					}
					checked = true;
				}
				// Otherwise, perform the unpruned moves and add them to the search stack
				cubeCpy.move(i);

				uint8_t estSuccMoves = depth + 1 + heuristic(cubeCpy);

				if (estSuccMoves <= estimate)
				{
					leaves.push({ cubeCpy, i, estSuccMoves });
				}
				else if (estSuccMoves < nextEstimate)
				{
					nextEstimate = estSuccMoves;
				}
			}

			while (!leaves.empty())
			{
				// Pushing sorted priqueue nodes into the search stack 
				stack.push({ leaves.top().cube, leaves.top().move, depth + 1 });
				leaves.pop();
			}
		}
	}

	// Appending small intermediate solution to main solution
	int j = 0;
	for (uint8_t i : interSolution)
	{
		if (i == 0xFF)
		{
			break;
		}
		if (depth + j < 30)
		{
			_solution[depth + j] = i;
		}
		j++;
	}

	if (depth + j < 30)
	{
		_solution[depth + j] = 0xFF;
	}

	return _solution;
}

