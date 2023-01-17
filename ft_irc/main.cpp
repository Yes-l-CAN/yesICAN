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
        std::cout << "./CanIRC [PASSWORD] [PORT]";
        return (1);
    }

    Utility util;
    static_cast<void>(util);

    CanServer serv;
    serv.s_On();

    return (0);
}