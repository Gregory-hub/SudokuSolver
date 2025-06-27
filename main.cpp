#include <iostream>
#include <string>

#include "Sudoku.h"

using std::string;
using std::getline;
using std::cin;
using std::cout;
using std::endl;


int main()
{
    Sudoku sudoku;
    cout << "SUDOKU SOLVER" << endl;
    cout << "Enter initial conditions" << endl;
    cout << "Format: row column digit" << endl;
    cout << "Example: 9 1 5" << endl;
    cout << "To print enter 'print'" << endl;
    cout << "To solve enter 'solve'" << endl;

    string input = "";

    while (true)
    {
        getline(std::cin, input);
        if (input == "print")
        {
            sudoku.PrintGrid();
        }
        else if (input != "solve")
        {
            sudoku.Solve();
            cout << "Sudoku solved:" << endl;
            sudoku.PrintGrid();
            break;
        }
        else if (input.length() != 5 || input[1] != ' ' || input[3] != ' ')
        {
            cout << "Invalid input. Try again" << endl;
        }
        else
        {
            int row = input[0] - '0';
            int col = input[2] - '0';
            int digit = input[4] - '0';
            try
            {
                sudoku.Add(row - 1, col - 1, digit);
                cout << "Entry added" << endl;
            }
            catch (std::out_of_range)
            {
                cout << "Invalid input. Try again" << endl;
            }
        }
    }
}
