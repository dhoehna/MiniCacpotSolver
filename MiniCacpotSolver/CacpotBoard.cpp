#pragma once
#include <Windows.h>
#include <array>
#include <list>
#include <wil/resource.h>
#include "CacpotBoard.h"
#include "CacpotBoardSpace.h"

namespace MiniCacpotSolver
{
    UINT c_BoardSpaceBeginning{ 0 };
    UINT c_BoardSpaceEnd{ 9 };
    UINT c_MaxWidth{ 3 };
    UINT c_MaxHeigth{ 3 };

    CacpotBoard::CacpotBoard() {};

    CacpotBoard::CacpotBoard(const CacpotBoard& right)
    {
        for (UINT y = 0; y < c_MaxHeigth; y++)
        {
            for (UINT x = 0; x < c_MaxWidth; x++)
            {
                CacpotSpace spaceToInsert{ right.GetAt(x, y) };

                if (spaceToInsert.XPosition() != UINT_MAX && spaceToInsert.YPosition() != UINT_MAX)
                {
                    Insert(spaceToInsert);
                }
            }
        }
    }

    CacpotBoard& CacpotBoard::operator=(const CacpotBoard& right)
    {
        for (UINT y = 0; y < c_MaxHeigth; y++)
        {
            for (UINT x = 0; x < c_MaxWidth; x++)
            {
                CacpotSpace spaceToInsert{ right.GetAt(x, y) };

                if (spaceToInsert.XPosition() != UINT_MAX && spaceToInsert.YPosition() != UINT_MAX)
                {
                    Insert(spaceToInsert);
                }
            }
        }

        return *this;
    }

    UINT SubscriptFromCoordinates(UINT x, UINT y)
    {
        return x + (c_MaxHeigth * y);
    }

    UINT XCoordinateFromSubscript(UINT subscript)
    {
        return subscript % c_MaxWidth;
    }

    UINT YCoordinateFromSubscript(UINT subscript)
    {
        return subscript / c_MaxHeigth;
    }

    LineTotal CacpotBoard::GetLineTotalAt(SumLine sumPosition) const
    {
        CacpotSpace one{};
        CacpotSpace two{};
        CacpotSpace three{};

        switch (sumPosition)
        {
        case SumLine::TopRow:
            one = m_Spaces[0];
            two = m_Spaces[1];
            three = m_Spaces[2];
            break;
        case SumLine::MiddleRow:
            one = m_Spaces[3];
            two = m_Spaces[4];
            three = m_Spaces[5];
            break;
        case SumLine::BottomRow:
            one = m_Spaces[6];
            two = m_Spaces[7];
            three = m_Spaces[8];
            break;
        case SumLine::LeftColumn:
            one = m_Spaces[0];
            two = m_Spaces[3];
            three = m_Spaces[6];
            break;
        case SumLine::MiddleColumn:
            one = m_Spaces[1];
            two = m_Spaces[4];
            three = m_Spaces[7];
            break;
        case SumLine::RightColumn:
            one = m_Spaces[2];
            two = m_Spaces[5];
            three = m_Spaces[8];
            break;
        case SumLine::TopLeftToBottomRight:
            one = m_Spaces[0];
            two = m_Spaces[4];
            three = m_Spaces[8];
            break;
        case SumLine::TopRightToBottomLeft:
            one = m_Spaces[2];
            two = m_Spaces[4];
            three = m_Spaces[6];
            break;
        default:
            THROW_HR_MSG(E_INVALIDARG, "Invalid SumLine passed in");
        }

        return one.GetRevealedNumber() + two.GetRevealedNumber() + three.GetRevealedNumber();
    }

    void CacpotBoard::Insert(const CacpotSpace& space)
    {
        UINT arrayPosition{ SubscriptFromCoordinates(space.XPosition(), space.YPosition()) };

        m_Spaces[arrayPosition] = space;

        m_RemainingNumbers.remove(space.GetRevealedNumber());
    }

    // inserts the number into the next avalible space.
    void CacpotBoard::Insert(UINT revealedNumber)
    {
        for (UINT index = c_BoardSpaceBeginning; index < c_BoardSpaceEnd; index++)
        {
            CacpotSpace& space{ m_Spaces[index] };

            if (space.IsEmpty())
            {
                CacpotSpace newSpace{ XCoordinateFromSubscript(index),
                YCoordinateFromSubscript(index), revealedNumber };

                Insert(newSpace);
                break;
            }
        }
    }

    void CacpotBoard::Insert(UINT xPosition, UINT yPosition, UINT revealedNumber)
    {
        if (xPosition < 0
            || xPosition > 3
            || yPosition < 0
            || yPosition > 3)
        {
            THROW_HR_MSG(E_INVALIDARG, "An invalid position was passed in");
        }

        Insert(CacpotSpace{ xPosition, yPosition, revealedNumber });
    }

    std::vector<UINT> CacpotBoard::GetRemainingNumbers() const
    {
        std::vector<UINT> remainingNumbers(m_RemainingNumbers.size(), 0);;

        int index{};

        for (auto&& remainingNumber : m_RemainingNumbers)
        {
            remainingNumbers[index++] = remainingNumber;
        }

        return remainingNumbers;
    }

    CacpotSpace CacpotBoard::GetAt(UINT xCoordinate, UINT yCoordinate) const
    {
        UINT arrayPosition{ SubscriptFromCoordinates(xCoordinate, yCoordinate) };

        return m_Spaces[arrayPosition];
    }
}