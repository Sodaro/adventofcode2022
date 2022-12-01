// day01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
int main()
{
    std::ifstream myfile("input.txt");
    std::string line;
    std::vector<unsigned long> elves;
    if (myfile.is_open())
    {
        unsigned long current_elf_calories = 0;
        while (std::getline(myfile, line))
        {
            if (line.size() == 0)
            {
                elves.push_back(current_elf_calories);
                current_elf_calories = 0;
                continue;
            }
            current_elf_calories += std::stoul(line);
        }
        elves.push_back(current_elf_calories);
        current_elf_calories += std::stoul(line);
        myfile.close();
    }
    std::sort(elves.begin(), elves.end());
    unsigned long top_three_sum = std::accumulate(elves.end() - 3, elves.end(), 0);

    std::cout << elves.back() << std::endl;
    std::cout << top_three_sum << std::endl;
}