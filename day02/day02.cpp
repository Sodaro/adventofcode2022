#include "../common.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
int main()
{
    std::map<char, char> winning_moves;
    winning_moves['A'] = 'Y';
    winning_moves['B'] = 'Z';
    winning_moves['C'] = 'X';
    std::map<char, char> losing_moves;
    losing_moves['A'] = 'Z';
    losing_moves['B'] = 'X';
    losing_moves['C'] = 'Y';

    int part1_score = 0;
    std::vector<std::string> lines = GetLinesInFile("input.txt");
    for (const auto& line : lines)
    {
        char opponent_option = line[0];
        char my_option = line[2];
        if ((int)(my_option - opponent_option) == 23)
            part1_score += 3;
        else
            part1_score += winning_moves[opponent_option] == my_option ? 6 : 0;
        part1_score += (int)(my_option - 'W');
    }

    int part2_score = 0;
    for (const auto& line : lines)
    {
        char opponent_option = line[0];
        char round_outcome = line[2];
        char my_option = '\0';
        bool is_draw = round_outcome == 'Y';
        bool is_win = round_outcome == 'Z';

        if (is_draw)
        {
            my_option = (char)(opponent_option + 23);
            part2_score += 3;
        }
        else if (is_win)
        {
            my_option = winning_moves[opponent_option];
            part2_score += 6;
        }
        else
        {
            my_option = losing_moves[opponent_option];
        }

        part2_score += (int)(my_option - 'W');
    }
    std::cout << part1_score << std::endl;
    std::cout << part2_score << std::endl;
}