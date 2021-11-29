#pragma once
#include <Windows.h>

namespace MiniCacpotSolver
{
    class CacpotSpace
    {
    public:
        CacpotSpace();
        CacpotSpace(const CacpotSpace& right);
        CacpotSpace(UINT xPosition, UINT yPosition, UINT revealedNumber);

        UINT GetRevealedNumber() const;

        UINT XPosition() const { return m_xPosition; }
        UINT YPosition() const { return m_yPosition; }
        bool IsEmpty() { return m_xPosition == UINT_MAX || m_yPosition == UINT_MAX; };

    private:
        UINT m_revealedNumber{};
        UINT m_xPosition{};
        UINT m_yPosition{};
    };
}