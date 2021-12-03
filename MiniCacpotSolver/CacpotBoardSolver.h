#pragma once
#include <vector>
#include <map>
#include "CacpotBoard.h"
#include "CacpotBoardPermutations.h"

namespace MiniCacpotSolver
{
    class CacpotBoardSolver
    {
    public:
        CacpotBoardSolver(CacpotBoard board);

        void AnalyzeAllPermutationsOfBoard() const;

    private:
        CacpotBoard m_Board;

        CacpotBoardPermutations GetAllPermutations() const;
        std::map<SumPosition, std::vector<LineTotal>> CountSums(std::vector<CacpotBoard> cacpotBoardPermutations) const;
        UINT Factorial(UINT number) const { return(number == 1 || number == 0) ? 1 : Factorial(number - 1) * number; }
    };
}