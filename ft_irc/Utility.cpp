#include "Utility.hpp"
#include <iostream>

std::vector<std::string> Utility::splitArr(char *s)
{
    std::vector<std::string> v;
    std::string str = static_cast<std::string>(s);
    size_t position = 0;
    size_t start = 0;
    
    if(str.find(" ") == std::string::npos)
    {
        throw(commandArgvException());
    }
    
    while ((position = str.find(" ", position)) != std::string::npos)
    {
        // std::cout << "start : " << start << std::endl;
        // std::cout << "pos : " << position << std::endl;
        std::string temp = "";
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

const char* Utility::commandArgvException::what() const throw() {
	return ("Command Acception error during spliting.");
}