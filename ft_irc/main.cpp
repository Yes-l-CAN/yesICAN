#include "CanChannel.hpp"
#include "CanClient.hpp"
#include "CanServer.hpp"
#include "Operation.hpp"
#include "Utility.hpp"

int main(int argc, char* argv[])
{
    static_cast<void>(argv);
    if (argc != 3)
    {
        std::cout << "./CanIRC [PORT] [PASSWORD]";
        return (1);
    }

    Operation operation;
    while(1)
        operation.Transmission();

    

    return (0);
}