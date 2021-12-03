#include "CacpotBoardPermutations.h"

namespace MiniCacpotSolver
{
    CacpotBoardPermutations::CacpotBoardPermutations(const std::vector<CacpotBoard>& cacpotBoards)
    {
        for (auto&& cacpotBoard : cacpotBoards)
        {
            m_permutations.push_back({ cacpotBoard });
        }
    }

    // Caclculates the sums for all positions for all boards.
    void CacpotBoardPermutations::CalculateSums()
    {
        for (auto&& cacpotPermutation : m_permutations)
        {
            cacpotPermutation.m_Totals = cacpotPermutation.m_Board.SumUpBoard();
        }
    }

    // Gets the number of times totals have shown up in each SumPosition
    // for each board.
    void CacpotBoardPermutations::GetCounts()
    {
        CalculateSums();
        // first index is the sum Position
        // second index is the sum at that position.
        std::vector<std::vector<LineTotal>> counts{};
        for (auto sumPosition = c_SumPositionMinimum; sumPosition < c_SumPositionMaximum; sumPosition++)
        {
            counts.push_back({});
            for (auto&& cacpotPermutation : m_permutations)
            {
                auto lineTotalAtSumPosition{ cacpotPermutation.m_Totals[sumPosition] };
                counts[sumPosition].push_back(lineTotalAtSumPosition);
            }
        }

        // now to put this into another structure.
        // each SumPosition has a different amount of LineTotals
        // It is now time to count those LineTOtals

        for (auto sumPosition = c_SumPositionMinimum; sumPosition < c_SumPositionMaximum; sumPosition++)
        {
            std::vector<SumPosition> countsOfLineTotals{std::vector<UINT>(c_MaximumSumAmount, 0)};
            auto lineTotals{ counts[sumPosition] };
            for (UINT index = 0; index < 120; index++)
            {
                countsOfLineTotals[lineTotals[index]]++;
            }
        }
    }
}
