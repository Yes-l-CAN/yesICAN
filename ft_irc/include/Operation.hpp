#ifndef OPERATION_HPP
#define OPERATION_HPP

#include "CanServer.hpp"
#include "CanClient.hpp"
#include "CanChannel.hpp"
#include "Operation.hpp"
#include "Utility.hpp"

#define SUCCESS 1
#define FAIL 0
#define ERROR -1

class Operation
{

private:
    int setFd;
    int result;
    CanServer* server;
    Utility     util;

protected:
    static const int bufferSize = 300;
    char buffer[bufferSize];

public:
    Operation();
    Operation(const Operation& obj);
    Operation& operator=(const Operation& obj);
    ~Operation();

    // socket transmission
    void    Transmission(); 

    // check command after parsing 
    void    CommandChecker(std::vector<std::string> argv);

    void cRecv(int fd);
    void Client2ServSend(int fd);
    void Serv2ClientSend(int fd);

    void Pass(std::vector<std::string> argv);
    int Nick(std::vector<std::string> argv);
    int User(std::vector<std::string> argv);
    void Ping(std::vector<std::string> argv);
    // void    Pong(std::vector<std::string> argv);
    void Join(std::vector<std::string> argv);
    void Part(std::vector<std::string> argv);
    void Kick(std::vector<std::string> argv);
    void Notice(std::vector<std::string> argv);
    void PrivateMSG(std::vector<std::string> argv);

    class recvException : public std::exception
    {
        virtual const char* what() const throw();
    };
};

#endif