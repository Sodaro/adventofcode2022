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
        auto elf1_start_time = std::stoi(elf1_timeslots[0]);
        auto elf2_start_time = std::stoi(elf2_timeslots[0]);
        auto elf1_end_time = std::stoi(elf1_timeslots[1]);
        auto elf2_end_time = std::stoi(elf2_timeslots[1]);

        if ((elf1_start_time <= elf2_start_time && elf1_end_time >= elf2_end_time) || (elf2_start_time <= elf1_start_time && elf2_end_time >= elf1_end_time))
            part1_overlap_count++;

        if ((elf1_start_time <= elf2_start_time && elf1_end_time >= elf2_start_time) || (elf2_start_time <= elf1_start_time && elf2_end_time >= elf1_start_time))
            part2_overlap_count++;

    }
    std::cout << part1_overlap_count << std::endl;
    std::cout << part2_overlap_count << std::endl;
}
