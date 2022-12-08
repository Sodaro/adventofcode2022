#include "../common.h"
#include <iostream>
#include <algorithm>
#include <functional>



int GetScenicScore(int x, int y, int tree_val, std::vector<std::string>& lines)
{
    int a = 0, b = 0, c = 0, d = 0;
    for (int _x = x+1; _x < lines.size(); _x++)
    {
        a++;
        if (lines[y][_x] >= tree_val)
            break;
    }
    for (int _x = x-1; _x >= 0; _x--)
    {
        b++;
        if (lines[y][_x] >= tree_val)
            break;
    }
    for (int _y = y+1; _y < lines.size(); _y++)
    {
        c++;
        if (lines[_y][x] >= tree_val)
            break;
    }
    for (int _y = y-1; _y >= 0; _y--)
    {
        d++;
        if (lines[_y][x] >= tree_val)
            break;
    }


    return a * b * c * d;
}

int GetHighestValue(int x, int y, const std::vector<std::string>& lines, std::function<bool(int&, int&)> comp)
{
    int max = INT_MIN;
    while (comp(x, y))
    {
        if (lines[y][x] > max)
            max = lines[y][x];
    }
    return max;
}

int main()
{
    auto lines = GetLinesInFile("input.txt");
    int nr_trees_visible_from_outside = 0; //outside edges visible always
    int highest_scenic_score = 0;
    int max_index = lines.size();
    int min_index = 0;

    for (int y = 0; y < max_index; y++)
    {
        for (int x = 0; x < max_index; x++)
        {
            auto y_max1 = GetHighestValue(x, y, lines, [](int& _x, int& _y) -> bool
                {
                    return --_y >= 0;
                });
            auto y_max2 = GetHighestValue(x, y, lines, [max_index](int& _x, int& _y) -> bool
                {
                    return ++_y < max_index;
                });

            auto x_max1 = GetHighestValue(x, y, lines, [](int& _x, int& _y) -> bool
                {
                    return --_x >= 0;
                });
            auto x_max2 = GetHighestValue(x, y, lines, [max_index](int& _x, int& _y) -> bool
                {
                    return ++_x < max_index;
                });
            
            auto tree_val = lines[y][x];
            if (tree_val > y_max1 || tree_val > y_max2 || tree_val > x_max1 || tree_val > x_max2)
                nr_trees_visible_from_outside++;

            auto score = GetScenicScore(x, y, tree_val, lines);
            if (score > highest_scenic_score)
                highest_scenic_score = score;

        }
    }
    std::cout << nr_trees_visible_from_outside << std::endl; //1647
    std::cout << highest_scenic_score << std::endl; //392080
}
