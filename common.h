#pragma once
#include <vector>
#include <string>
#include <fstream>

std::vector<std::string> GetWords(std::string str, char delim)
{
    std::vector<std::string> words;
    std::string word = "";
    for (const auto& x : str)
    {
        if (x == delim)
        {
            words.emplace_back(word);
            word = "";
        }
        else
        {
            word = word + x;
        }
    }
    return words;
}

std::vector<std::string> GetLinesInFile(const char* path)
{
	std::ifstream myfile(path);
	std::string line;
	std::vector<std::string> lines;
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			lines.emplace_back(line);
		}
	}
	myfile.close();
	return lines;
}