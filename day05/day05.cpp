#include "../common.h"
#include <iostream>
int main()
{
    std::vector<std::string> lines = GetLinesInFile("input.txt");
    std::vector<std::string> part1_crates{"", "", "", "", "", "", "", "", ""};
    int i;
    for (i = 0; i < lines.size(); i++)
    {
        auto& line = lines[i];
        if (line.size() == 0 || line[1] == '1')
            break;

        for (int j = 1; j < line.size(); j += 4)
        {
            if (line[j] == ' ')
                continue;

            part1_crates[j / 4].push_back(line[j]);
        }
    }
    std::vector<std::string> part2_crates(part1_crates.begin(), part1_crates.end());
    for (i = i+2; i < lines.size(); i++)
    {
        auto& line = lines[i];
        auto params = GetWords(line, ' ');
        int count = std::stoi(params[1]);
        int start_index = std::stoi(params[3]) - 1;
        int target_index = std::stoi(params[5]) - 1;

        for (int j = 0; j < count; j++)
        {
            auto& start = part1_crates[start_index];
            auto& target = part1_crates[target_index];
            target.insert(target.begin(), start[0]);
            start.erase(0, 1);
        }

        auto& start = part2_crates[start_index];
        std::string chunk = start.substr(0, count);
        start.erase(0, count);
        auto& target = part2_crates[target_index];
        target.insert(0, chunk);
    }

    auto print_result = [](const std::vector<std::string>& vec)
    {
        std::string result = "";
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i].empty())
                continue;

            result.push_back(vec[i].front());
        }
        std::cout << result << std::endl;
    };
    print_result(part1_crates);
    print_result(part2_crates);
}
