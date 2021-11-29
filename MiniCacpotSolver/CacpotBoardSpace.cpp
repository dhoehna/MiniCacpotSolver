#pragma once
#include <Windows.h>
#include "CacpotBoardSpace.h"
#include <wil/resource.h>

namespace MiniCacpotSolver
{
    CacpotSpace::CacpotSpace() : m_xPosition(UINT_MAX), m_yPosition(UINT_MAX) {}

    CacpotSpace::CacpotSpace(const CacpotSpace& right)
    {
        m_xPosition = right.m_xPosition;
        m_yPosition = right.m_yPosition;
        m_revealedNumber = right.m_revealedNumber;
    }

    CacpotSpace::CacpotSpace(UINT xPosition, UINT yPosition, UINT revealedNumber)
        : m_revealedNumber(revealedNumber), m_xPosition(xPosition), m_yPosition(yPosition) 
    {
        THROW_HR_IF_MSG(E_INVALIDARG, revealedNumber < 1 || revealedNumber > 9, "Revealed number can only be between 0 and 9");
        THROW_HR_IF_MSG(E_INVALIDARG, xPosition < 0 || xPosition > 3, "xPosition number can only be between 0 and 3");
        THROW_HR_IF_MSG(E_INVALIDARG, yPosition < 0 || yPosition > 9, "yPosition number can only be between 0 and 3");
    }

    UINT CacpotSpace::GetRevealedNumber() const { return m_revealedNumber; }
}
