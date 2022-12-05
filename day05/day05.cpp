#include "../common.h"
#include <iostream>
#include <deque>
int main()
{
    std::vector<std::string> lines = GetLinesInFile("input.txt");
    std::vector<std::deque<char>> part1_crates;
    std::vector<std::deque<char>> part2_crates;

    for (int i = 0; i < lines[0].size() / 3; i++)
    {
        part1_crates.emplace_back(std::deque<char>());
        part2_crates.emplace_back(std::deque<char>());
    }

    bool reading_moves = false;
    for (const auto& line : lines)
    {
        if (line.size() == 0 || line[1] == '1')
        {
            reading_moves = true;
            continue;
        }
        if (!reading_moves)
        {
            for (int i = 1; i < line.size(); i += 4)
            {
                if (line[i] == ' ')
                    continue;

                int index = i / 4;
                part1_crates[index].emplace_back(line[i]);
                part2_crates[index].emplace_back(line[i]);
            }
        }
        else
        {
            auto params = GetWords(line, ' ');
            int count = std::stoi(params[1]);
            int start_index = std::stoi(params[3])-1;
            int target_index = std::stoi(params[5])-1;

            std::string chunk = "";
            for (int i = 0; i < count; i++)
            {
                auto crate = part1_crates[start_index].front();
                part1_crates[target_index].emplace_front(crate);
                part1_crates[start_index].pop_front();
                
                crate = part2_crates[start_index].front();
                part2_crates[start_index].pop_front();
                chunk.push_back(crate);
            }
            for (int i = chunk.size()-1; i >= 0; i--)
            {
                auto crate = chunk[i];
                part2_crates[target_index].emplace_front(crate);
            }
        }
    }
    std::string result1 = "";
    
    for (int i = 0; i < part1_crates.size(); i++)
    {
        if (part1_crates[i].empty())
            continue;

        result1.push_back(part1_crates[i].front());
    }
    std::cout << result1 << std::endl;

    std::string result2 = "";
    for (int i = 0; i < part2_crates.size(); i++)
    {
        if (part2_crates[i].empty())
            continue;

        result2.push_back(part2_crates[i].front());
    }
    std::cout << result2 << std::endl;
}
