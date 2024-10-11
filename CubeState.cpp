#include "CubeState.h"
#include <iostream>

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

CubeState::CubeState(std::array<uint8_t, 12> edge, std::array<uint8_t, 8> corner)
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

std::array<uint8_t, 12> CubeState::getEdges()
{
    return _edges;
}
std::array<uint8_t, 8> CubeState::getCorners()
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

void CubeState::display()
{
    std::cout << "Edge array: \n";
    for (unsigned i = 0; i < 12; i++)
    {
        std::cout << unsigned(_edges[i]) << " ";
    }

    std::cout << "\nCorner array: \n";
    for (unsigned i = 0; i < 8; i++)
    {
        std::cout << unsigned(_corners[i]) << " ";
    }
}

std::list<std::string> CubeState::solveCorners()
{

}

CubeState& CubeState::move(int move)
{
    switch (move)
    {
        case 0:
            return this->u();
        case 1:
            return this->u2();
        case 2:
            return this->u3();
        case 3:
            return this->r();
        case 4:
            return this->r2();
        case 5:
            return this->r3();
        case 6:
            return this->f();
        case 7:
            return this->f2();
        case 8:
            return this->f3();
        case 9:
            return this->d();
        case 10:
            return this->d2();
        case 11:
            return this->d3();
        case 12:
            return this->l();
        case 13:
            return this->l2();
        case 14:
            return this->l3();
        case 15:
            return this->b();
        case 16:
            return this->b2();
        case 17:
            return this->b3();
    }
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
    std::swap(_edges[0], _edges[2]);
    std::swap(_edges[1], _edges[3]);

    std::swap(_corners[0], _corners[2]);
    std::swap(_corners[1], _corners[3]);

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
    _corners[2] = _corners[3];
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
    std::swap(_edges[1], _edges[9]);
    std::swap(_edges[5], _edges[6]);

    std::swap(_corners[1], _corners[6]);
    std::swap(_corners[2], _corners[5]);

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
    std::swap(_edges[2], _edges[10]);
    std::swap(_edges[6], _edges[7]);

    std::swap(_corners[3], _corners[6]);
    std::swap(_corners[2], _corners[7]);

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

CubeState& CubeState::d()
{

    uint8_t temp = _edges[8];
    _edges[8] = _edges[9];
    _edges[9] = _edges[10];
    _edges[10] = _edges[11];
    _edges[11] = temp;

    temp = _corners[4];
    _corners[4] = _corners[5];
    _corners[5] = _corners[6];
    _corners[6] = _corners[7];
    _corners[7] = temp;

    return *this;
}

CubeState& CubeState::d2()
{
    std::swap(_edges[8], _edges[10]);
    std::swap(_edges[9], _edges[11]);

    std::swap(_corners[4], _corners[6]);
    std::swap(_corners[5], _corners[7]);

    return *this;
}

CubeState& CubeState::d3()
{
    uint8_t temp = _edges[8];
    _edges[8] = _edges[11];
    _edges[11] = _edges[10];
    _edges[10] = _edges[9];
    _edges[9] = temp;

    temp = _corners[4];
    _corners[4] = _corners[7];
    _corners[7] = _corners[6];
    _corners[6] = _corners[5];
    _corners[5] = temp;

    return *this;
}

CubeState& CubeState::l()
{
    uint8_t temp = _edges[3];
    _edges[3] = flip(_edges[4]);
    _edges[4] = flip(_edges[11]);
    _edges[11] = flip(_edges[7]);
    _edges[7] = flip(temp);

    temp = _corners[0];
    _corners[0] = counterClockwise(_corners[4]);
    _corners[4] = clockwise(_corners[7]);
    _corners[7] = counterClockwise(_corners[3]);
    _corners[3] = clockwise(temp);

    return *this;
}

CubeState& CubeState::l2()
{
    std::swap(_edges[3], _edges[11]);
    std::swap(_edges[4], _edges[7]);

    std::swap(_corners[0], _corners[7]);
    std::swap(_corners[3], _corners[4]);

    return *this;
}

CubeState& CubeState::l3()
{
    uint8_t temp = _edges[3];
    _edges[3] = flip(_edges[7]);
    _edges[7] = flip(_edges[11]);
    _edges[11] = flip(_edges[4]);
    _edges[4] = flip(temp);

    temp = _corners[0];
    _corners[0] = counterClockwise(_corners[3]);
    _corners[3] = clockwise(_corners[7]);
    _corners[7] = counterClockwise(_corners[4]);
    _corners[4] = clockwise(temp);

    return *this;
}

CubeState& CubeState::b()
{
    uint8_t temp = _edges[0];
    _edges[0] = _edges[5];
    _edges[5] = _edges[8];
    _edges[8] = _edges[4];
    _edges[4] = temp;

    temp = _corners[0];
    _corners[0] = clockwise(_corners[1]);
    _corners[1] = counterClockwise(_corners[5]);
    _corners[5] = clockwise(_corners[4]);
    _corners[4] = counterClockwise(temp);

    return *this;
}

CubeState& CubeState::b2()
{
    std::swap(_edges[0], _edges[8]);
    std::swap(_edges[4], _edges[5]);

    std::swap(_corners[0], _corners[5]);
    std::swap(_corners[1], _corners[4]);

    return *this;
}

CubeState& CubeState::b3()
{
    uint8_t temp = _edges[0];
    _edges[0] = _edges[4];
    _edges[4] = _edges[8];
    _edges[8] = _edges[5];
    _edges[5] = temp;

    temp = _corners[0];
    _corners[0] = clockwise(_corners[4]);
    _corners[4] = counterClockwise(_corners[5]);
    _corners[5] = clockwise(_corners[1]);
    _corners[1] = counterClockwise(temp);

    return *this;
}