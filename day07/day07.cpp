#include "../common.h"
#include <iostream>
#include <map>


struct Directory
{
    std::string path = "";
    Directory* parent = nullptr;
    std::map<std::string, Directory*> directories;
    std::map<std::string, int> files;
};

void PrintContent(const Directory* directory)
{
    std::cout << directory->path << std::endl;
    for (const auto& file_pair : directory->directories)
    {
        std::cout << file_pair.first << std::endl;
    }

    for (const auto& file_pair : directory->files)
    {
        //std::cout << current_path << " " << val << std::endl;
        std::cout << file_pair.first << " size: " << file_pair.second << std::endl;
    }
}

int GetDirectorySize(Directory* directory, int upper_threshold, int& total_size)
{
    int directory_size = 0;
    for (const auto& pair : directory->directories)
    {
        auto size = GetDirectorySize(pair.second, upper_threshold, total_size);
        directory_size += size;
    }
    for (const auto& pair : directory->files)
    {
        directory_size += pair.second;
    }

    if (directory_size <= upper_threshold)
        total_size += directory_size;

    return directory_size;
}

int FindSmallestDirectoryOverThreshold(Directory* directory, int threshold, int& smallest_over_threshold)
{
    int directory_size = 0;
    for (const auto& pair : directory->directories)
    {
        auto size = FindSmallestDirectoryOverThreshold(pair.second, threshold, smallest_over_threshold);
        if (size >= threshold && size <= smallest_over_threshold)
            smallest_over_threshold = size;

        directory_size += size;
    }
    for (const auto& pair : directory->files)
    {
        directory_size += pair.second;
    }

    return directory_size;
}

int main()
{
    Directory root;
    root.path = "/";
    Directory* current_directory = &root;
    auto lines = GetLinesInFile("test.txt");
    int available_space = 70000000;
    for (int i = 1; i < lines.size(); i++) //skipping first line as it's cd '/', which is what we use for root dir
    {
        auto words = GetWords(lines[i], ' ');
        if (words[1] == "ls")
        {
            //ls was always called after creating a fresh dir, which means that one is empty
            //and never prints anything, printing parent instead
            if (current_directory->parent != nullptr) 
                PrintContent(current_directory->parent);
        }
        else if (words[0] == "dir")
        {
            //Create directory
            std::string new_path = current_directory->path + words[1] + "/";
            auto new_dir = new Directory();
            new_dir->parent = current_directory;
            new_dir->path = new_path;
            current_directory->directories.emplace(new_path, new_dir);
        }
        else if (words[1] == "cd")
        {
            if (words[2] == "..")
            {
                //go up one directory
                current_directory = current_directory->parent;
            }
            else
            {
                //step into directory
                std::string target_path = current_directory->path + words[2] + "/";
                current_directory = current_directory->directories[target_path];
            }
        }
        else
        {
            int size = std::stoi(words[0]);
            current_directory->files[current_directory->path + words[1]] = size; //create file
            available_space -= size;
        }
    }

    //--------------PART1-----------------
    int amount_under_threshold = 0;
    GetDirectorySize(&root, 100000, amount_under_threshold);
    std::cout << amount_under_threshold << std::endl;

    //--------------PART2-----------------
    int needed_space_for_update = 30000000;
    int amount_to_free = needed_space_for_update - available_space;
    int smallest_over_threshold = INT_MAX;
    FindSmallestDirectoryOverThreshold(&root, amount_to_free, smallest_over_threshold);
    std::cout << smallest_over_threshold << std::endl;
}
