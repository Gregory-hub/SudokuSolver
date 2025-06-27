#include <utility>
#include <stdexcept>
#include <list>
#include <array>
#include <queue>
#include <iostream>

using std::list;
using std::array;
using std::queue;


class Sudoku
{
    int m_Grid[9][9];

public:
    Sudoku()
    {
        for (size_t i = 0; i < 9; ++i)
            for (size_t j = 0; j < 9; ++j)
                m_Grid[i][j] = 0;
    }

    void Add(int row, int col, int digit)
    {
        if (row < 0 || row > 8 || col < 0 || col > 8)
            throw std::out_of_range("Row or column out of grid bounds (9x9)");

        if (digit < 1 || digit > 9)
            throw std::out_of_range("Digit for sudoku sell out of range (1 to 9)");

        m_Grid[row][col] = digit;
    }

    void Solve()
    {
        array<list<int>, 81> adjacencyList = ConstructGraph();
        array<int, 81> vertices = FlattenGrid();

        ColorGraph(adjacencyList, vertices);

        for (size_t i = 0; i < vertices.size(); ++i)
            m_Grid[i / 9][i % 9] = vertices[i];
    }

    void PrintGrid()
    {
        for (size_t row = 0; row < 9; ++row)
        {
            for (size_t col = 0; col < 9; ++col)
            {
                if (m_Grid[row][col])
                    std::cout << m_Grid[row][col] << "  ";
                else
                    std::cout << '.' << "  ";
            }
            std::cout << std::endl;
        }
    }

private:
    bool ColorGraph(array<list<int>, 81>& adjacencyList, array<int, 81>& vertices, int v = 0)
    {
        if (v >= 81)
            return true;

        bool immutable = false;
        if (vertices[v] != 0)
            return ColorGraph(adjacencyList, vertices, v + 1);

        int color = 1;
        while (true)
        {
            if (!IsValidColor(adjacencyList, vertices, v, color))
            {
                ++color;
            }
            else
            {
                vertices[v] = color;
                if (!ColorGraph(adjacencyList, vertices, v + 1))
                {
                    vertices[v] = 0;
                    ++color;
                }
                else
                {
                    return true;
                }
            }

            if (color > 9)
                return false;
        }
    }

    bool IsValidColor(array<list<int>, 81>& adjacencyList, array<int, 81>& vertices, int v, int color)
    {
        for (int n : adjacencyList[v])
        {
            if (vertices[n] == color)
                return false;
        }
        return true;
    }

    array<int, 81> FlattenGrid()
    {
        array<int, 81> vertices;
        vertices.fill(0);
        for (size_t i = 0; i < 9; ++i)
            for (size_t j = 0; j < 9; ++j)
                vertices[9 * i + j] = m_Grid[i][j];
        return vertices;
    }

    array<list<int>, 81> ConstructGraph()
    {
        array<list<int>, 81> adjacencyList;
        BindRowsColumns(adjacencyList);
        BindSectors(adjacencyList);
        return adjacencyList;
    }

    void BindRowsColumns(array<list<int>, 81>& adjacencyList)
    {
        for (size_t row = 0; row < 9; ++row)
        {
            for (size_t col = 0; col < 9; ++col)
            {
                for (size_t i = 0; i < 9; ++i)
                {
                    if (i != col)
                        adjacencyList[9 * row + col].push_back(9 * row + i);
                }

                for (size_t i = 0; i < 9; ++i)
                {
                    if (i != row)
                        adjacencyList[9 * row + col].push_back(9 * i + col);
                }
            }
        }
    }

    void BindSectors(array<list<int>, 81>& adjacencyList)
    {
        for (size_t s_row = 0; s_row < 9; s_row += 3)
        {
            for (size_t s_col = 0; s_col < 9; s_col += 3)
            {
                BindSector(adjacencyList, s_row, s_col);
            }
        }
    }

    void BindSector(array<list<int>, 81>& adjacencyList, size_t s_row, size_t s_col)
    {
        for (size_t row = s_row; row < s_row + 3; ++row)
        {
            for (size_t col = s_col; col < s_col + 3; ++col)
            {
                for (size_t r = s_row; r < s_row + 3; ++r)
                {
                    for (size_t c = s_col; c < s_col + 3; ++c)
                    {
                        // Assuming rows and columns already binded
                        if (!(row == r || col == c))
                            adjacencyList[9 * row + col].push_back(9 * r + c);
                    }
                }
            }
        }
    }
};
