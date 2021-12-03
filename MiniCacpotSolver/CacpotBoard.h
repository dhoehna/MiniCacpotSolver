#pragma once
#include <Windows.h>
#include <array>
#include <vector>
#include <list>
#include <wil/resource.h>
#include "CacpotBoardSpace.h"
#include "CommonTypeDefs.h"
#include "CommonEnums.h"
#include "Constants.h"

namespace MiniCacpotSolver
{
    class CacpotBoard
    {
    public:
        CacpotBoard();
        CacpotBoard(const CacpotBoard& right);

        CacpotBoard& operator=(const CacpotBoard& other);

        void Insert(UINT revealedNumber);
        void Insert(const CacpotSpace& space);
        void Insert(UINT xPosition, UINT yPosition, UINT revealedNumber);
        CacpotSpace GetAt(UINT xCoordinate, UINT yCoordinate) const;
        std::vector<UINT> GetRemainingNumbers() const;
        std::vector<LineTotal> SumUpBoard() const;

    private:
        std::array<CacpotSpace, 9> m_Spaces{};
        std::list<UINT> m_RemainingNumbers{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        LineTotal GetLineTotalAt(SumLine sumPosition) const;
    };
}