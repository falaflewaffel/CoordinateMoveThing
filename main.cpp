#include "pch.h"
#include <Windows.h>
#include <cmath>
#include <array>
#include <iostream>

constexpr int gridSize{ 6 }; // grid is a square
constexpr char playerIcon{ 'o' };
constexpr char spaceIcon{ '_' }; // probably could be better

enum Direction
{
    up,
    left,
    down,
    right,
};


class Point
{
private:
    int m_x{ 0 };
    int m_y{ 0 };

public:
    Point() : Point(0, 0) {}

    Point(int x, int y)
        : m_x {x}
        , m_y {y}
    {}

    int x() { return m_x; }
    int y() { return m_y; }
    void setCoords(int x, int y)
    {
        // player wraps around if they go off-screen
        if (x >= 0)
            m_x = x % gridSize;
        else
            m_x = x + gridSize;

        if (y >= 0)
            m_y = y % gridSize;
        else
            m_y = y + gridSize;
    }
};


class Game
{
private:
    Point m_point{0, 0}; // 4th column, 4th row
    std::array<bool, 4> m_wasPreviouslyPressed{}; // could use a bitset whatever but im too silly :3
    bool m_needsDrawn{ true };
    
public:
    void draw()
    {
        system("cls");

        // print rows above the player with empty spaces
        for (int i{ 0 }; i < m_point.y(); ++i)
        {
            for (int j{ 0 }; j < gridSize; ++j)
            {
                std::cout << spaceIcon;
            }
            std::cout << '\n';
        }

        // print row that the player is on
        for (int i{ 0 }; i < m_point.x(); ++i)
        {
            std::cout << spaceIcon;
        }

        std::cout << playerIcon;

        // print spaces after the player
        for (int i{ m_point.x() + 1 }; i < gridSize; ++i)
        {
            std::cout << spaceIcon;
        }

        std::cout << '\n';

        // print rows under the player
        for (int i{ m_point.y() + 1 }; i < gridSize; ++i)
        {
            for (int j{ 0 }; j < gridSize; ++j)
            {
                std::cout << spaceIcon;
            }
            std::cout << '\n';
        }
    }

    void updateState()
    {
        m_needsDrawn = false; // reset flag so it doesn't stay true if we don't need to redraw


        // HANDLE LEFT KEYPRESS
        if (GetAsyncKeyState(VK_LEFT) && !m_wasPreviouslyPressed[left]) // left initially pressed
        {
            m_point.setCoords(m_point.x() - 1, m_point.y());
            m_wasPreviouslyPressed[left] = true;
            m_needsDrawn = true;
        }
        else if (!GetAsyncKeyState(VK_LEFT) && m_wasPreviouslyPressed[left]) // left released
        {
            m_wasPreviouslyPressed[left] = false;
        }

        // HANDLE RIGHT KEYPRESS
        if (GetAsyncKeyState(VK_RIGHT) && !m_wasPreviouslyPressed[right]) // right initially pressed
        {
            m_point.setCoords(m_point.x() + 1, m_point.y());
            m_wasPreviouslyPressed[right] = true;
            m_needsDrawn = true;
        }
        else if (!GetAsyncKeyState(VK_RIGHT) && m_wasPreviouslyPressed[right]) // right released
        {
            m_wasPreviouslyPressed[right] = false;
        }

        // HANDLE UP KEYPRESS
        if (GetAsyncKeyState(VK_UP) && !m_wasPreviouslyPressed[up]) // up initially pressed
        {
            m_point.setCoords(m_point.x(), m_point.y() - 1);
            m_wasPreviouslyPressed[up] = true;
            m_needsDrawn = true;
        }
        else if (!GetAsyncKeyState(VK_UP) && m_wasPreviouslyPressed[up]) // up released
        {
            m_wasPreviouslyPressed[up] = false;
        }

        // HANDLE DOWN KEYPRESS
        if (GetAsyncKeyState(VK_DOWN) && !m_wasPreviouslyPressed[down]) // down initially pressed
        {
            m_point.setCoords(m_point.x(), m_point.y() + 1);
            m_wasPreviouslyPressed[down] = true;
            m_needsDrawn = true;
        }
        else if (!GetAsyncKeyState(VK_DOWN) && m_wasPreviouslyPressed[down]) // down released
        {
            m_wasPreviouslyPressed[down] = false;
        }
    }


    void loop()
    {
        if (m_needsDrawn)
        {
            draw();
            m_needsDrawn = false;
        }
        updateState();
        
    }
};


int main()
{
    Game g{};
    while (true)
    {
        g.loop();
    }

    return 0;
}
