#pragma once
#include <Windows.h>

namespace MiniCacpotSolver
{
    const UINT c_SumLineMinimum{ 0 };
    const UINT c_SumLineMaximum{ 7 };

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