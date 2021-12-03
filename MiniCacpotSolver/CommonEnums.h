#pragma once
#include <Windows.h>

namespace MiniCacpotSolver
{
    enum SumLine
    {
        TopRow = 0,
        MiddleRow,
        BottomRow,
        LeftColumn,
        MiddleColumn,
        RightColumn,
        TopLeftToBottomRight,
        TopRightToBottomLeft
    };
}