#include "./include/Utility.hpp"

std::vector<std::string> Utility::splitArr(std::string& str)
{

    std::vector<std::string> v;
    size_t                   position = 0;
    size_t                   start = 0;

    std::string temp;
    while ((position = str.find(" ", position)) != std::string::npos)
    {
        // std::cout << "start : " << start << std::endl;
        // std::cout << "pos : " << position << std::endl;
        temp = "";
        for (size_t i = start; i < position; i++)
        {
            temp += str[i];
        }
        v.push_back(temp);
        position += 1;
        start = position;
    }

    return (v);
}