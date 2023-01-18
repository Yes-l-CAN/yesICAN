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

<<<<<<< HEAD
Operation::Operation(const Operation &obj)
=======
Operation::Operation(const Operation& obj)
>>>>>>> 4f0a9949f75b0494eb182f5d2f3aa773d724c115
{
    *this = obj;
}

// deep copy
<<<<<<< HEAD
Operation &Operation::operator=(const Operation &obj)
=======
Operation& Operation::operator=(const Operation& obj)
>>>>>>> 4f0a9949f75b0494eb182f5d2f3aa773d724c115
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

<<<<<<< HEAD
        CanServer *dummy = this->server;
=======
        CanServer* dummy = this->server;
>>>>>>> 4f0a9949f75b0494eb182f5d2f3aa773d724c115
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
<<<<<<< HEAD
            CanClient   *targetClient = findClient(this->setFd);
            std::vector<std::string> cmd = util.splitArr(this->buffer);
            CommandChecker(cmd, targetClient);
        }
        catch (std::exception &e)
=======
            std::vector<std::string> cmd = util.splitArr(this->buffer);

            CommandChecker(cmd);
        }
        catch (std::exception& e)
>>>>>>> 4f0a9949f75b0494eb182f5d2f3aa773d724c115
        {
            std::cout << e.what() << std::endl;
        }
    }
    // command 따라서 파싱 하고 실행..?
    // write 테스트
}

CanClient   *Operation::findClient(int fd)
{   
    return (server->getClientList().find(fd)->second);
}

void Operation::CommandChecker(std::vector<std::string> argv, CanClient* targetClient)
{
    std::string cmd[] = {"PASS", "NICK", "USER", "PING", "JOIN", "PART", "KICK", "NOTICE", "PRIVMSG", "QUIT"};

    for (int i = 0; i < sizeof(cmd) / sizeof(std::string); i++)
    {
        if (argv.front() == cmd[i])
        {
<<<<<<< HEAD
            
            switch (i)
            {
            case 0:
                this->Pass(argv, targetClient);
                return;
            case 1:
                this->Nick(argv, targetClient);
                return;
            case 2:
                this->User(argv, targetClient);
                return;
            case 3:
                this->Ping(argv, targetClient);
                return;
            case 4:
                this->Join(argv, targetClient);
                return;
            case 5:
                this->Part(argv, targetClient);
                return;
            case 6:
                this->Kick(argv, targetClient);
                return;
            case 7:
                this->Notice(argv, targetClient);
                return;
            case 8:
                this->PrivateMSG(argv, targetClient);
=======
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
>>>>>>> 4f0a9949f75b0494eb182f5d2f3aa773d724c115
                return;
            default:;
                //  인자가 더해져 들어옴! (자동)
                // ./jisookim #42Seoul : hihi!
            }
        }
    }
}

void Operation::cRecv(int fd)
<<<<<<< HEAD
=======
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
>>>>>>> 4f0a9949f75b0494eb182f5d2f3aa773d724c115
{
    int ret = recv(fd, buffer, bufferSize, 0);
    if (ret < 0)
        throw(CanException::recvSocketErrorException());
    if (ret == 0)
        throw(CanException::recvSocketClosedException()); // TODO: make exception more specifically.
}

void Operation::Client2ServSend(int fd)
{
    // need to think about it more ...
}

void Operation::Serv2ClientSend(int fd)
{
    // need to think about it more ...
}


void Operation::Pass(std::vector<std::string> argv, CanClient* targetClient)
{
    // std::cout << "Pass Called!" << std::endl;
    std::vector<std::string>::iterator it;
    it = argv.end() - 1;
    if (*it == this->server->getPassWord())
        targetClient->setMemberLevel(PASS_FIN);
    else
        throw(CanException::pwIncorrectException());
}

int Operation::Nick(std::vector<std::string> argv, CanClient* targetClient)
{
    std::cout << "Nick called" << std::endl;
    std::string replyStr;
    // std::cout << "Nick Called!" << std::endl;
    std::vector<std::string>::iterator it;
    it = argv.end() - 1;
    //  std::map<int, CanClient*>::iterator it2 = server->getClientList().begin();
    // std::cout << "it : " << *it << std::endl;
    // std::cout << "it2 : " << server->getClientList().begin()->first << std::endl;
    for( std::map<int, CanClient*>::iterator it2 = server->getClientList().begin(); it2 != server->getClientList().end(); ++it2)
    {
        if(it2->second->getNickname() == *it)
            throw(CanException::existNickException());
    }
    targetClient->setNickname(*it);
    if (targetClient->getMemberLevel() == USER_FIN)
        targetClient->setMemberLevel(CERTIFICATION_FIN);
    else
        targetClient->setMemberLevel(NICK_FIN);
    //need to replace -> server2Clientsend()
    replyStr = *argv.begin() + *(argv.end() - 1);
    std::cout << "reply:: " << replyStr << std::endl;
    return (0);
}

int Operation::User(std::vector<std::string> argv, CanClient* targetClient)
{
    //std::cout << "User Called!" << std::endl;
    std::vector<std::string>::iterator it;
    it = argv.end() - 1;
    std::map<int, CanClient*>::iterator it2;
    for(it2 = server->getClientList().begin(); it2 != server->getClientList().end(); it2++)
    {
        if(it2->second->getUsername() == *it)
            throw(CanException::existUserException());
    }
    targetClient->setUsername(*it);
    if (targetClient->getMemberLevel() == NICK_FIN)
        targetClient->setMemberLevel(CERTIFICATION_FIN);
    else
        targetClient->setMemberLevel(USER_FIN);
    return (0);
}

void Operation::Ping(std::vector<std::string> argv, CanClient* targetClient)
{
    if (targetClient->getMemberLevel() != CERTIFICATION_FIN)
        throw(CanException::NotCertificatedException());
    // send 'pong'
    std::cout << "ping Called!" << std::endl;
}

// void    Pong(std::vector<std::string> argv, CanClient* targetClient);
void Operation::Join(std::vector<std::string> argv, CanClient* targetClient)
{
    std::cout << "join Called!" << std::endl;
}

void Operation::Part(std::vector<std::string> argv, CanClient* targetClient)
{
    std::cout << "part Called!" << std::endl;
}

void Operation::Kick(std::vector<std::string> argv, CanClient* targetClient)
{
    std::cout << "kick Called!" << std::endl;
}

void Operation::Notice(std::vector<std::string> argv, CanClient* targetClient)
{
    std::cout << "notice Called!" << std::endl;
}

void Operation::PrivateMSG(std::vector<std::string> argv, CanClient* targetClient)
{
    std::cout << "privatemsg Called!" << std::endl;
}
