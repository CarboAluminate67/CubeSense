#include "cubestate.hpp"

CubeState::CubeState()
{
    for (unsigned i = 0; i < 12; i++)
    {
        _edges[i] = i;
    }
    for (unsigned i = 0; i < 8; i++)
    {
        _corners[i] = i;
    }
}

CubeState::CubeState(array<uint8_t, 12> edge, array<uint8_t, 8> corner)
{
    for (int i = 0; i < 12; i++)
    {
        _edges[i] = edge[i];
    }
    for (int i = 0; i < 8; i++)
    {
        _corners[i] = corner[i];
    }
}

array<uint8_t, 12> CubeState::getEdges()
{   
    return _edges;
}
array<uint8_t, 8> CubeState::getCorners()
{
    return _corners;
}

uint8_t CubeState::flip(uint8_t edgeInd)
{
    return (edgeInd + 12) % 24;
}

uint8_t CubeState::clockwise(uint8_t cornerInd)
{
    return (cornerInd + 8) % 24;
}

uint8_t CubeState::counterClockwise(uint8_t cornerInd)
{
    return (cornerInd + 16) % 24;
}

bool CubeState::solvedState()
{
    for (int i = 0; i < 12; i++)
    {
        if (_edges[i] != i)
        {
            return false;
        }
    }
    for (int i = 0; i < 8; i++)
    {
        if (_corners[i] != i)
        {
            return false;
        }
    }
    return true;
}
                          
CubeState& CubeState::u() // Edge Change:   {0, 1, 2, 3, 4, 5, 6 , 7, 8, 9, 10, 11} -> {3, 0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11}
{                         // Corner Change: {0, 1, 2, 3, 4, 5, 6, 7}                -> {3, 0, 1, 2, 4, 5, 6, 7}

    uint8_t temp = _edges[0];
    _edges[0] = _edges[3];
    _edges[3] = _edges[2];
    _edges[2] = _edges[1];
    _edges[1] = temp;

    temp = _corners[0];
    _corners[0] = _corners[3];
    _corners[3] = _corners[2];
    _corners[2] = _corners[1];
    _corners[1] = temp;

    return *this;
}

CubeState& CubeState::u2()
{
    swap(_edges[0], _edges[2]);
    swap(_edges[1], _edges[3]);

    swap(_corners[0], _corners[2]);
    swap(_corners[1], _corners[3]);

    return *this;
}

CubeState& CubeState::u3()
{
    uint8_t temp = _edges[0];
    _edges[0] = _edges[1];
    _edges[1] = _edges[2];
    _edges[2] = _edges[3];
    _edges[3] = temp;

    temp = _corners[0];
    _corners[0] = _corners[1];
    _corners[1] = _corners[2];
    _corners[3] = _corners[3];
    _corners[3] = temp;

    return *this;
}

CubeState& CubeState::r()
{
    uint8_t temp = _edges[1];
    _edges[1] = flip(_edges[6]);
    _edges[6] = flip(_edges[9]);
    _edges[9] = flip(_edges[5]);
    _edges[5] = flip(temp);

    temp = _corners[1];
    _corners[1] = clockwise(_corners[2]);
    _corners[2] = counterClockwise(_corners[6]);
    _corners[6] = clockwise(_corners[5]);
    _corners[5] = counterClockwise(temp);

    return *this;
}

CubeState& CubeState::r2()
{
    swap(_edges[1], _edges[9]);
    swap(_edges[5], _edges[6]);

    swap(_corners[1], _corners[6]);
    swap(_corners[2], _corners[5]);

    return *this;
}

CubeState& CubeState::r3()
{
    uint8_t temp = _edges[1];
    _edges[1] = flip(_edges[5]);
    _edges[5] = flip(_edges[9]);
    _edges[9] = flip(_edges[6]);
    _edges[6] = flip(temp);

    temp = _corners[1];
    _corners[1] = clockwise(_corners[5]);
    _corners[5] = counterClockwise(_corners[6]);
    _corners[6] = clockwise(_corners[2]);
    _corners[2] = counterClockwise(temp);

    return *this;
}

CubeState& CubeState::f()
{
    uint8_t temp = _edges[2];
    _edges[2] = _edges[7];
    _edges[7] = _edges[10];
    _edges[10] = _edges[6];
    _edges[6] = temp;

    temp = _corners[2];
    _corners[2] = clockwise(_corners[3]);
    _corners[3] = counterClockwise(_corners[7]);
    _corners[7] = clockwise(_corners[6]);
    _corners[6] = counterClockwise(temp);

    return *this;
}

CubeState& CubeState::f2()
{
    swap(_edges[2], _edges[10]);
    swap(_edges[6], _edges[7]);

    swap(_corners[3], _corners[6]);
    swap(_corners[2], _corners[7]);

    return *this;
}

CubeState& CubeState::f3()
{
    uint8_t temp = _edges[2];
    _edges[2] = _edges[6];
    _edges[6] = _edges[10];
    _edges[10] = _edges[7];
    _edges[7] = temp;

    temp = _corners[2];
    _corners[2] = clockwise(_corners[6]);
    _corners[6] = counterClockwise(_corners[7]);
    _corners[7] = clockwise(_corners[3]);
    _corners[3] = counterClockwise(temp);

    return *this;
}


