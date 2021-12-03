#pragma once

#include <vector>
#include <map>
#include "CacpotBoard.h"
#include "CommonTypeDefs.h"
#include "Constants.h"

namespace MiniCacpotSolver
{
    class CacpotBoardPermutations
    {
    public:
        CacpotBoardPermutations(const std::vector<CacpotBoard>& cacpotBoards);

        void GetCounts();

    private:

        struct CacpotBoardInformation
        {
            CacpotBoard m_Board;
            std::vector<LineTotal> m_Totals;
        };

        std::vector<CacpotBoardInformation> m_permutations{};

        void CalculateSums();
    };
}

