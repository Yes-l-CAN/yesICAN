#include "Operation.hpp"
#include "Utility.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <vector>

Operation::Operation()
{
    std::cout << "constructor" << std::endl;
    this->server = new CanServer();
    this->server->s_On();
}

Operation::Operation(const Operation& obj)
{
    *this = obj;
}

// deep copy
Operation& Operation::operator=(const Operation& obj)
{
    if (this != &obj)
    {

        this->setFd = obj.setFd;
        this->result = obj.result;
        for (int i = 0; i < bufferSize; i++)
        {
            this->buffer[i] = obj.buffer[i];
        }

        // deep copy
        Operation replica(obj);

        CanServer* dummy = this->server;
        this->server = replica.server;
    }
    return *this;
}

Operation::~Operation()
{
    delete server;
}

void Operation::Transmission()
{
    server->s_Select();
    this->setFd = server->Transmission(); // return i(fd)
    if (this->setFd == server->getSocketFd())
    {
        std::cout << "accept client " << std::endl;
    }
    else
    {
        try
        {
            cRecv(this->setFd);
            std::vector<std::string> cmd = util.splitArr(this->buffer);

            CommandChecker(cmd);
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    // command 따라서 파싱 하고 실행..?
    // write 테스트
}

void Operation::CommandChecker(std::vector<std::string> argv)
{
    std::string cmd[] = {"PASS", "NICK", "USER", "PING", "JOIN", "PART", "KICK", "NOTICE", "PRIVMSG", "QUIT"};

    for (int i = 0; i < sizeof(cmd) / sizeof(std::string); i++)
    {
        if (argv.front() == cmd[i])
        {
            switch (i)
            {
            case 0:
                this->Pass(argv);
                return;
            case 1:
                this->Nick(argv);
                return;
            case 2:
                this->User(argv);
                return;
            case 3:
                this->Ping(argv);
                return;
            case 4:
                this->Join(argv);
                return;
            case 5:
                this->Part(argv);
                return;
            case 6:
                this->Kick(argv);
                return;
            case 7:
                this->Notice(argv);
                return;
            case 8:
                this->PrivateMSG(argv);
                return;
            case 9:
                this->Quit(argv);
                return;
            default:;
                //  인자가 더해져 들어옴! (자동)
                // ./jisookim #42Seoul : hihi!
            }
        }
    }
}

void Operation::cRecv(int fd)
{
    int ret = recv(fd, buffer, bufferSize, 0);
    if (ret < 0)
        throw(recvException());
    if (ret == 0)
        throw(recvException()); // TODO: make exception more specifically.
}

void Operation::Client2ServSend(int fd)
{
    // need to think about it more ...
}

void Operation::Serv2ClientSend(int fd)
{
    // need to think about it more ...
}

void Operation::Pass(std::vector<std::string> argv)
{
    std::cout << "PAss Called!" << std::endl;
}

int Operation::Nick(std::vector<std::string> argv)
{
    std::cout << "Nick Called!" << std::endl;
}

int Operation::User(std::vector<std::string> argv)
{
    std::cout << "User Called!" << std::endl;
}

void Operation::Ping(std::vector<std::string> argv)
{
    std::cout << "ping Called!" << std::endl;
}

// void    Pong(std::vector<std::string> argv);
void Operation::Join(std::vector<std::string> argv)
{
    std::cout << "join Called!" << std::endl;
}

void Operation::Part(std::vector<std::string> argv)
{
    std::cout << "part Called!" << std::endl;
}

void Operation::Kick(std::vector<std::string> argv)
{
    std::cout << "kick Called!" << std::endl;
}

void Operation::Notice(std::vector<std::string> argv)
{
    std::cout << "notice Called!" << std::endl;
}

void Operation::PrivateMSG(std::vector<std::string> argv)
{
    std::cout << "privatemsg Called!" << std::endl;
}

void Operation::Quit(std::vector<std::string> argv)
{
    std::cout << "quit Called!" << std::endl;
}

const char* Operation::recvException::what() const throw()
{
    return ("recv() exception occured!\n");
}