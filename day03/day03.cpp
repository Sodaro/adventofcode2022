// day03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../common.h"
#include <iostream>
#include <map>

int main()
{
    std::vector<std::string> lines = GetLinesInFile("input.txt");
    int priority_sum = 0;
    for (const auto& line : lines)
    {
        std::string compartment1, compartment2;
        auto mid_point = line.size() / 2;
        compartment1 = line.substr(0, mid_point);
        compartment2 = line.substr(mid_point, line.size() - mid_point);

        char common = '\0';
        for (int i = 0; i < mid_point; i++)
        {
           if (compartment2.find(compartment1[i]) != std::string::npos)
           {
               common = compartment1[i];
               break;
           }
        }
        if (common - '`' >= 0)
            priority_sum += common - '`';
        else
            priority_sum += common - '@' + 26;
    }
    std::cout << priority_sum << std::endl;

    priority_sum = 0;
    for (int i = 0; i < lines.size() - 2; i += 3)
    {
        std::string line1, line2, line3;
        line1 = lines[i];
        line2 = lines[i+1];
        line3 = lines[i+2];

        char common = '\0';
        for (int i = 0; i < line1.size(); i++)
        {
            if (line2.find(line1[i]) != std::string::npos && line3.find(line1[i]) !=  std::string::npos)
            {
                common = line1[i];
                break;
            }
        }
        if (common - '`' >= 0)
            priority_sum += common - '`';
        else
            priority_sum += common - '@' + 26;
    }
    std::cout << priority_sum << std::endl;
}
