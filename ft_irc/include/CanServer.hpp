#ifndef CAN_SERVER_HPP
#define CAN_SERVER_HPP

#include <iostream>
#include <cerrno>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <exception>

#include <utility>
#include <map>

#include "CanClient.hpp"

#define MPORT 4242

#define MAX_FD 1000
#define MAXBUF 10


class CanServer
{
private:
	int			 port;
	std::string	password;

	int socketFd;
	struct sockaddr_in addr;

	fd_set reads;
	fd_set copyReads;

	int		maxFd;
	
	std::map<int, CanClient*>	clientList;
	
public:
	CanServer();
	CanServer(const CanServer& obj);
	CanServer& operator=(const CanServer& obj);
	~CanServer();
	
	void setServer(char	*port, char	*pw);
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

	class socketCreateException: public std::exception{
		virtual const char*	what() const throw();
	};

	class bindException: public std::exception{
		virtual const char* what() const throw();
	};
	
	class listenException: public std::exception
	{
		virtual const char* what() const throw();
	};

	class selectException: public std::exception
	{
		virtual const char* what() const throw();
	};

	class acceptException: public std::exception
	{
		virtual const char* what() const throw();
	};

	class invalidPortException: public std::exception
	{
		virtual const char* what() const throw();
	};

};



#endif