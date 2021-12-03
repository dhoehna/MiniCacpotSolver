#include "CacpotBoardSolver.h"
#include <wil/resource.h>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>

namespace MiniCacpotSolver
{
    /*const std::vector<CacpotScores> c_ValueToPoints{
    {6, 10000},
    {24, 3600},
    {23, 1800},
    {21, 1080},
    {8, 720},
    {9, 360},
    {20, 306},
    {11, 252},
    {15, 180},
    {17, 180},
    {22, 144},
    {18, 119},
    {12, 108},
    {10, 80},
    {13, 72},
    {16, 72},
    {14, 54},
    {7, 36},
    {19, 36}
    };*/

    CacpotBoardSolver::CacpotBoardSolver(CacpotBoard board)
    {
        m_Board = board;
    }

    CacpotBoardPermutations CacpotBoardSolver::GetAllPermutations() const
    {
        std::vector<CacpotBoard> cacpotScores{};

        std::vector<UINT> remainingNumbers{ m_Board.GetRemainingNumbers() };
        UINT permutationArray[5];

        CacpotBoard tempBoard{ m_Board };
        int index{};
        for (auto&& remainingNumber : remainingNumbers)
        {
            tempBoard.Insert(remainingNumber);
            permutationArray[index++] = remainingNumber;
        }

        cacpotScores.push_back(tempBoard);

        while (std::next_permutation(permutationArray, permutationArray + 5))
        {
            CacpotBoard tempBoard{ m_Board };

            for (auto&& remainingNumber : permutationArray)
            {
                tempBoard.Insert(remainingNumber);
            }

            cacpotScores.push_back(tempBoard);
        }

        return CacpotBoardPermutations{ cacpotScores };
    }

    // This returns a map of sum position to
    // a vector that organizes the chances by value,
    // not by MGP.  We want MGP to percentage.
    // std::vector<SumPosition> each one has a list of tuple<MGP, chance>
    // right.  Sum position 0 can have a sum of 6 - 24.  
    // Convert any chances that has a chance greater than 0
    // to MGP gained.
    // A vector of cacpot scores.
    void CacpotBoardSolver::AnalyzeAllPermutationsOfBoard() const
    {
        auto permutations{ GetAllPermutations() };
        permutations.GetCounts();
    }
}