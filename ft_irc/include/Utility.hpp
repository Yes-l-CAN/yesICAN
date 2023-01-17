#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <vector>
#include <exception>

class Utility
{
private:
public:
    std::vector<std::string> splitArr(char * str);
    
    class commandArgvException: public std::exception
    {
        virtual const char* what() const throw();
    };
    
};

#endif