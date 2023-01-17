#ifndef CAN_SERVER_HPP
#define CAN_SERVER_HPP

#include <arpa/inet.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <map>
#include <utility>

#include "CanClient.hpp"
#include "CanServer.hpp"

#define MPORT 4244

#define MAX_FD 1000
#define MAXBUF 10


class CanServer
{
private:
    int port;
    std::string password;

    int socketFd;
    struct sockaddr_in addr;

    fd_set reads;
    fd_set copyReads;

    int maxFd;

    std::map<int, CanClient*>           clientList;     // current exist all clients list
    std::map<std::string, CanChannel*>  channelList;    // current exist all channel list

public:
    CanServer();
    CanServer(const CanServer& obj);
    CanServer& operator=(const CanServer& obj);
    ~CanServer();

    void setServer(char* port, char* pw);
    void s_On();
    // void serverOff();

    void setServAddr();
    void s_Socket();
    void s_Bind();
    void s_Listen();
    void s_Select();
    void s_Accept();

    // utils
    void setFdSet();
    void findFd();
    
    void addChannelElement(const std::string channelName, CanChannel* pNewChannel);       // add channel List
    void deleteChannelElement(const std::string channelName);    // delete channel List


    // socket transmission
    int  Transmission(); 

    //getter
    int  getSocketFd() const;

    class socketCreateException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class bindException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class listenException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class selectException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class acceptException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class invalidPortException : public std::exception
    {
        virtual const char* what() const throw();
    };
};

#endif