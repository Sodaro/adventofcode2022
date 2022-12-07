#include "../common.h"
#include <iostream>
#include <map>

void PrintContent(std::map<std::string, std::vector<unsigned long>> directories, std::string current_path)
{
    std::cout << current_path << std::endl;
    for (const auto& val : directories[current_path])
    {
        std::cout << current_path << " " << val << std::endl;
    }
}

void FindDirectoryOfSizeSmaller(std::map<std::string, std::vector<unsigned long>> directories, unsigned long upper_threshold)
{
    //TODO: e is missing file
    unsigned long total_sum = 0;
    for (const auto& pair : directories)
    {
        unsigned long directory_sum = 0;
        for (const auto& val : pair.second)
        {
            directory_sum += val;
        }
        if (directory_sum < upper_threshold)
            total_sum += directory_sum;
    }
    std::cout << total_sum << std::endl;
}

int main()
{
    //std::vector<std::string> directory_paths;
    std::map<std::string, std::vector<unsigned long>> directories;
    auto lines = GetLinesInFile("test.txt");
    std::string current_directory_path = "";
    directories[current_directory_path] = std::vector<unsigned long> ();
    for (int i = 1; i < lines.size(); i++)
    {
        auto words = GetWords(lines[i], ' ');
        if (words[1] == "ls")
            PrintContent(directories, current_directory_path);
        else if (words[0] == "dir")
        {
            directories.emplace(current_directory_path + "/" + words[1], std::vector<unsigned long>{});
        }
        else if (words[1] == "cd")
        {
            if (words[2] == "..")
            {
                current_directory_path = current_directory_path.substr(0, current_directory_path.find_last_of('/'));
            }
            else
            {
                current_directory_path += "/" + words[2];
            }
        }
        else
        {
            directories[current_directory_path].emplace_back(std::stoul(words[0]));
        }
    }
    FindDirectoryOfSizeSmaller(directories, 100000);
}
