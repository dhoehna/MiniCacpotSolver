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

    std::vector<CacpotBoard> CacpotBoardSolver::GetAllPermutations() const
    {
        std::vector<CacpotBoard> cacpotScores{};

        std::vector<UINT> remainingNumbers{ m_Board.GetRemainingNumbers() };
        UINT permutationArray[5];

        CacpotBoard tempBoard{ m_Board };
        int index{};
        for (auto&& remainingNumber : remainingNumbers)
        {
            tempBoard.Insert(remainingNumber);
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

        return cacpotScores;
    }

    // The vector ranges from 0 to 25.
    // The index of the vector is total from the sum position.
    // Valid totals are 6 through 24.
    // positions 0 - 5 are not used and may contain garbage.
    std::map<SumPosition, std::vector<LineTotal>> CacpotBoardSolver::CountSums(std::vector<CacpotBoard> cacpotBoardPermutations) const
    {
        std::map<SumPosition, std::vector<LineTotal>> sumPositionToCountOfSums{};

        // for each permutation
        // for each sum position
        // get sum
        // keep track of the sum for that line and board.
        // What we want is to say
        // For the sum position 0 there is an X percent chance
        // that it will be 6, or 10000MGP.
        // To answer this question we need to keep track of
        // Sum position
        // number of times each sum has come up for that position.
        // We need a map of the sunPosition.  Each entry has
        // 1. the value
        // 2. the number of times it has come up.
        // Either a map of SumPosition to a list of tuples, or
        // a list where the index is the SumPosition.
        // I would call this CacpotPermutations.
        // Well.  Why not?
        // CacpotPermutations holds a what we need?
        // Basically we need a conversion from a list of CacpotBoards
        // to something above to hold the LinePosition, Value, count of value.

        /*for (auto&& sumPositionToListOfSum : sumPositionToListOfSums)
        {
            sumPositionToCountOfSums.insert({ sumPositionToListOfSum.first, std::vector<LineTotal>(25, 0) });
            for (auto lineTotal = c_SumMinimum; lineTotal <= c_SumMaximum; lineTotal++)
            {
                UINT count{};
                for (auto&& total : sumPositionToListOfSum.second)
                {
                    if (total == lineTotal)
                    {
                        count++;
                    }
                }

                sumPositionToCountOfSums[sumPositionToListOfSum.first][lineTotal] = count;
            }
        }*/

        return sumPositionToCountOfSums;
    }

    std::map<SumPosition, std::vector<double>> CacpotBoardSolver::CalculateLineTotalChances(std::map<SumPosition, std::vector<LineTotal>> SumPositionToCountOfSums) const
    {
        std::map<SumPosition, std::vector<double>> sumPostionToSumChance{};
        UINT numberOfPermutations = static_cast<double>(Factorial(5));
        for (auto&& sumPositionToCount : SumPositionToCountOfSums)
        {
            auto sumPosition{sumPositionToCount.first};
            sumPostionToSumChance.insert({ sumPosition, std::vector<double>(25, 0) });

            for (LineTotal lineTotal = c_SumMinimum; lineTotal <= c_SumMaximum; lineTotal++)
            {
                auto countOfLineTotal{ static_cast<double>(sumPositionToCount.second[lineTotal]) };
                double chance{static_cast<double>(countOfLineTotal) / numberOfPermutations};

                sumPostionToSumChance[sumPosition][lineTotal] = chance;
            }
        }

        return sumPostionToSumChance;
    }

    // This returns a map of sum position to
    // a vector that organizes the chances by value,
    // not by MGP.  We want MGP to percentage.
    // std::vector<SumPosition> each one has a list of tuple<MGP, chance>
    // right.  Sum position 0 can have a sum of 6 - 24.  
    // Convert any chances that has a chance greater than 0
    // to MGP gained.
    // A vector of cacpot scores.
    std::map<SumPosition, std::vector<double>> CacpotBoardSolver::AnalyzeAllPermutationsOfBoard() const
    {
        auto sumPositionToListOfSums{ SumUpAllPermutations ()};
        auto sumPositionToCountOfSums{ CountSums(sumPositionToListOfSums) };
        return CalculateLineTotalChances (sumPositionToCountOfSums);
    }
}