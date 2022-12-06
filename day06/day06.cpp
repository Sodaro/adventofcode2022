#include "../common.h"
#include <iostream>
#include <set>
#include <thread>
bool IsMarker(std::string marker, int num_chars_in_marker)
{
	std::set<char> unique_set;
	int num_chars_processed = 0;
	for (const auto& c : marker)
	{
		num_chars_processed++;
		unique_set.emplace(c);
		if (num_chars_processed != unique_set.size()) //all chars must be unique, don't process rest if false
			return false;
	}
	return unique_set.size() == num_chars_in_marker;
}

bool ValidateMarkers(std::vector<std::string>& markers, int num_chars_in_marker)
{
	for (int i = markers.size()-1; i >= 0; i--)
	{
		if (markers[i].size() < num_chars_in_marker) //if less than required don't process at all
			continue;

		if (IsMarker(markers[i], num_chars_in_marker))
			return true;

		markers.erase(markers.begin() + i);
	}
	return false;
}

void AddToMarkers(std::vector<std::string>& markers, char c, int num_chars_in_marker)
{
	for (int i = markers.size()-2; i >= 0; i--)
	{
		markers[i].push_back(c);
	}
}

void SolvePart(const std::vector<std::string>& lines, int num_chars_in_marker)
{
	std::vector<std::string> potential_markers;
	int number_chars_processed = 0;
	for (const auto& line : lines)
	{
		for (const auto& c : line)
		{
			number_chars_processed++;
			potential_markers.push_back(std::string(1, c));
			AddToMarkers(potential_markers, c, num_chars_in_marker);
			if (ValidateMarkers(potential_markers, num_chars_in_marker))
				break;
		}
		potential_markers.clear();
	}
	std::cout << number_chars_processed << std::endl;
}

int main()
{
	auto lines = GetLinesInFile("input.txt");
	std::thread part1(SolvePart, lines, 4);
	std::thread part2(SolvePart, lines, 14);
	part1.join();
	part2.join();
}