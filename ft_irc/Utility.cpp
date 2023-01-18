#include "Utility.hpp"
#include <iostream>

std::vector<std::string> Utility::splitArr(char *s)
{
    std::vector<std::string> v;
    std::string str = static_cast<std::string>(s);
    std::string temp = "";
    size_t position = 0;
    size_t start = 0;
    
    if(str.find(" ") == std::string::npos)
    {
        throw(commandArgvException());
    }
    
    while ((position = str.find(" ", position)) != std::string::npos)
    {
        std::string temp = "";
        for (size_t i = start; i < position; i++)
        {
            temp += str[i];
        }
        v.push_back(temp);
        position += 1;
        start = position;
    }
    if(position == std::string::npos)
        position = str.length();
    for (size_t i = start; i < position; i++)
        temp += str[i];
    v.push_back(temp);

    return (v);
}

const char* Utility::commandArgvException::what() const throw() {
	return ("Command Acception error during spliting.");
}