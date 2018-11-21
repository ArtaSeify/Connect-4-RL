#pragma once
#include <array>

namespace Connect4
{
    const static int RSIZE = 6;
    const static int CSIZE = 7;

    const static char PLAYER_ONE = 'R';
    const static char PLAYER_TWO = 'Y';

    using BoardType = std::array<std::array<bool, RSIZE>, CSIZE>;
    using VectorType = std::array<char, CSIZE>;
}