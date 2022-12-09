#include "../common.h"
#include <iostream>
#include <unordered_set>
#include <math.h>
#include <Windows.h>

void ResetCaretPosition()
{
    //move the caret to the beginning, so that when we write it will overwrite the existing output
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    std::cout.flush();
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void PrintState(std::vector<std::string>& lines)
{
    ResetCaretPosition();
    std::string output = "";
    for (const auto& line : lines)
    {
        output += line + "\n";
    }

    std::cout << output << std::endl;
}

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};
struct Tail
{
    int row_pos = 0;
    int col_pos = 0;
    char tail_symbol = 'T';
    Tail* tail = nullptr;
    std::unordered_set<std::string> visited_positions;
    std::vector<std::string>& level;
    Tail(char symbol, int row, int col, std::vector<std::string>& p_level) : tail_symbol(symbol), row_pos(row), col_pos(col), level(p_level)
    {
        level[row][col] = 'T';
        StorePosition(row, col);
    };
    void StorePosition(int row, int col)
    {
        std::string position = std::to_string(row) + ';' + std::to_string(col);
        visited_positions.emplace(position);
    }
    void Move(int current_row, int current_col)
    {
        int prev_row = row_pos, prev_col = col_pos;
        auto dist = std::abs(current_row - row_pos) + std::abs(current_col - col_pos);

        int target_row_offset = current_row - row_pos;
        int target_col_offset = current_col - col_pos;
        bool should_move = false;
        if (current_row == row_pos || current_col == col_pos)
        {
            should_move = dist > 1;
        }
        else
        {
            should_move = dist > 2;
        }
        if (should_move)
        {
            int row_move_length = 0, col_move_length = 0;

            if (target_col_offset != 0)
                col_move_length = target_col_offset > 0 ? 1 : -1;

            if (target_row_offset != 0)
                row_move_length = target_row_offset > 0 ? 1 : -1;

            row_pos += row_move_length;
            col_pos += col_move_length;

            level[row_pos][col_pos] = tail_symbol;
            if (level[prev_row][prev_col] == '9')
                level[prev_row][prev_col] = '#';

            StorePosition(row_pos, col_pos);
            if (tail != nullptr)
                tail->Move(row_pos, col_pos);
        }
    }
};

struct Head
{
    int row_pos = 0;
    int col_pos = 0;
    Tail& tail;
    std::vector<std::string>& level;
    Head(int row, int col, Tail& p_tail, std::vector<std::string>& p_level) : row_pos(row), col_pos(col), level(p_level), tail(p_tail)
    {
        level[row][col] = 'H';
    };
    void Move(Direction dir)
    {
        int prev_row = row_pos;
        int prev_col = col_pos;
        switch (dir)
        {
        case Direction::Up:
            row_pos -= 1;
            break;
        case Direction::Down:
            row_pos += 1;
            break;
        case Direction::Left:
            col_pos -= 1;
            break;
        case Direction::Right:
            col_pos += 1;
            break;
        default:
            break;
        }
        if (level[prev_row][prev_col] == 'H')
            level[prev_row][prev_col] = '.';

        tail.Move(row_pos, col_pos);
        level[row_pos][col_pos] = 'H';
    }
};

int main()
{
    int grid_width = 20;
    int grid_height = 20;
    std::vector<std::string> level;
    std::string row(grid_width, '.');
    for (int i = 0; i < grid_height; i++)
    {
        level.emplace_back(row);
    }

    Tail tail_pieces[9] = { 
        { '1', grid_height / 2, grid_width / 2, level },
        { '2', grid_height / 2, grid_width / 2, level },
        { '3', grid_height / 2, grid_width / 2, level },
        { '4', grid_height / 2, grid_width / 2, level },
        { '5', grid_height / 2, grid_width / 2, level },
        { '6', grid_height / 2, grid_width / 2, level },
        { '7', grid_height / 2, grid_width / 2, level },
        { '8', grid_height / 2, grid_width / 2, level },
        { '9', grid_height / 2, grid_width / 2, level },
    };

    for (int i = 0; i < 8; i++)
    {
        tail_pieces[i].tail = &tail_pieces[i + 1];
    }
    Head head(grid_height / 2, grid_width / 2, tail_pieces[0], level);
    auto lines = GetLinesInFile("test.txt");
    for (const auto& line : lines)
    {
        auto args = GetWords(line, ' ');
        int count = std::stoi(args[1]);
        for (int i = 0; i < count; i++)
        {
            //PrintState(level);
            if (args[0] == "U")
            {
                head.Move(Direction::Up);
            }
            else if (args[0] == "D")
            {
                head.Move(Direction::Down);
            }
            else if (args[0] == "L")
            {
                head.Move(Direction::Left);
            }
            else
            {
                head.Move(Direction::Right);
            }
            //Sleep(32);
        }
    }
    std::cout << tail_pieces[0].visited_positions.size() << std::endl; //part1 6406 correct
    std::cout << tail_pieces[8].visited_positions.size() << std::endl; //part2 2643 correct
}
