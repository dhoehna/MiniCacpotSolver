#pragma once
#include <vector>
#include <map>
#include "CacpotBoard.h"

namespace MiniCacpotSolver
{
    class CacpotBoardSolver
    {
    public:
        CacpotBoardSolver(CacpotBoard board);

        std::map<UINT, std::vector<double>> AnalyzeAllPermutationsOfBoard() const;

    private:
        CacpotBoard m_Board;

        std::vector<CacpotBoard> GetAllPermutations() const;
        std::map<SumPosition, std::vector<LineTotal>> CountSums(std::vector<CacpotBoard> cacpotBoardPermutations) const;
        std::map<SumPosition, std::vector<double>> CalculateLineTotalChances(std::map<SumPosition, std::vector<LineTotal>> SumPositionToCountOfSums) const;
        UINT Factorial(UINT number) const { return(number == 1 || number == 0) ? 1 : Factorial(number - 1) * number; }
    };
}