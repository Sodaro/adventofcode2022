#include "../common.h"
#include <iostream>

int main()
{
    std::vector<std::string> lines = GetLinesInFile("input.txt");
    int part1_overlap_count = 0;
    int part2_overlap_count = 0;
    for (const auto& line : lines)
    {
        std::vector<std::string> sections = GetWords(line, ',');
        auto elf1_timeslots = GetWords(sections[0], '-');
        auto elf2_timeslots = GetWords(sections[1], '-');
        auto start1 = std::stoi(elf1_timeslots[0]);
        auto start2 = std::stoi(elf2_timeslots[0]);
        auto end1 = std::stoi(elf1_timeslots[1]);
        auto end2 = std::stoi(elf2_timeslots[1]);

        auto inside_range = [](auto low_num, auto high_num, auto low_range, auto high_range)
        {
            return low_range <= low_num && high_range >= high_num;
        };

        if (inside_range(start2, end2, start1, end1) || inside_range(start1, end1, start2, end2))
            part1_overlap_count++;

        if (inside_range(start2, start2, start1, end1) || inside_range(start1, start1, start2, end2))
            part2_overlap_count++;

    }
    std::cout << part1_overlap_count << std::endl;
    std::cout << part2_overlap_count << std::endl;
}
