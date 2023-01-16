#include "./include/CanClient.hpp"
#include "./include/CanServer.hpp"
#include "./include/CanChannel.hpp"
#include "./include/Operation.hpp"
#include "./include/Utility.hpp"

int main(int argc, char* argv[]){

    if (argc != 3)
    {
        std::cout << "./CanIRC [PASSWORD] [PORT]";
        return (1);
    }

    Utility util; 

    CanServer serv;
    serv.s_On();
    
    

    return (0);

}