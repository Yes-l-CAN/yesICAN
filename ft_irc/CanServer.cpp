#include "CanServer.hpp"

CanServer::CanServer() : socketFd(-1), maxFd(1000)
{
    // Default Constructor
    setServAddr();
    FD_ZERO(&reads);
    FD_ZERO(&copyReads);
	
}

CanServer::~CanServer()
{
    // Destuctor
	std::map<int, CanClient*>::iterator it;
	if (this->clientList->empty() == true)
	{
		return ;
	}

	for (it = this->clientList->begin(); it != this->clientList->end(); it++)
	{
		close(it->first);
		if (it->second != NULL)
		{
			delete it->second;
		}
	}
	this->clientList->clear();
}

CanServer::CanServer(const CanServer& obj){
    // Copy Constructor
    *this = obj;
}

CanServer& CanServer::operator=(const CanServer& obj){
    // Assignment operator
    if (this != &obj)
	{

	}
	return (*this);
}

// setter
void CanServer::setServer(char *port, char *pw){
	this->port = std::atoi(port);
	if(this->port < 1025 || this->port > 65536)
		throw(CanException::invalidPortException());
	this->password = static_cast<std::string>(pw);
}

void CanServer::s_On(){
	try{
		s_Socket();

		// 포트 점유 방지
		int option = true;
		setsockopt(this->socketFd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
		
		setServAddr();
		s_Bind();
		s_Listen();
		setFdSet();
		std::cout << "server on!" << std::endl;
 	} catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}
    // implement server logic here
}

void CanServer::setServAddr()
{
    this->addr.sin_family = AF_INET;
    this->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->addr.sin_port = htons(this->inputPortNum); 
}

void CanServer::s_Socket(){
	int	fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd < 0)
		throw (CanException::socketCreateException());
	this->socketFd = fd;
}

void CanServer::s_Bind(){
	int		res;

	res = bind(this->socketFd, (struct sockaddr*)&(this->addr), sizeof(this->addr));
	if(res < 0)
		throw(CanException::bindException());
}

void CanServer::s_Listen()
{
	if (listen(this->socketFd, MAX_FD) < 0)
    {
        throw(CanException::listenException());
    }
}

void CanServer::s_Select()
{
	int		res;
	struct timeval	timeout;

	while(1){
		timeout.tv_sec = 5;
		timeout.tv_usec = 500;
		this->copyReads = this->reads;

		res = select(this->maxFd + 1, &(this->copyReads), NULL, NULL, &timeout);
		std::cout << "res : " << res << "\n";
		if(res < 0)
			throw (CanException::selectException());
		else if(res == 0)
			continue;
		else
			break;
	}
}

void CanServer::s_Accept()
{
	int clientSockFd = -1;
	struct sockaddr_in clientAddr;
	unsigned int size = sizeof(clientAddr);

	
	clientSockFd = accept(this->socketFd, (struct sockaddr*)&clientAddr, &size);
	if (clientSockFd < 0)
	{
		throw (CanException::acceptException());
	}
	FD_SET(clientSockFd, &reads);

	CanClient *temp = new CanClient(clientAddr);
	clientList->insert(std::make_pair(clientSockFd, temp));
	std::cout << "Client list first: fd" ;
	std::cout << clientList->begin()->first << std::endl;
	std::cout << "client list second: client";
	std::cout << clientList->begin()->second->getMemberLevel()<< std::endl;
}

// utils
void CanServer::setFdSet()
{
    fd_set* reads_addr = &this->reads;
    FD_ZERO(reads_addr);
    FD_SET(this->socketFd, reads_addr);
}

void CanServer::setInputPassword(char* str)
{
	this->inputPassword = str;
}

void CanServer::setInputPortNum(char* str)
{
	this->inputPortNum = atoi(str);
}

void CanServer::findFd(){
	//너무...너무... 안 이쁜.... 넣고나니 빼는게 나을 듯 한....
	// for(int i = 0; i < this->maxFd + 1; i++)
	for(int i = 3; i < this->maxFd + 1; i++)
	{
		// if(FD_ISSET(i, &this->copyReads) && i == this->socketFd)
		if(FD_ISSET(i, &this->copyReads) == this->socketFd)
		{
			try {
				s_Accept();
			} catch(std::exception &e) {
				std::cout << e.what() << std::endl;
				return ;
			}
		}
	}
}

// socket transmission
int CanServer::Transmission()
{
	for(int i = 0; i < this->maxFd; i++)
	{
		if(FD_ISSET(i, &(this->copyReads)))
		{
			if(i == this->socketFd)
			{
				s_Accept();
				std::cout << "Accepted socket fd!\n";
			}
			return (i);
		} 
	}
	return (-1);
}

//getter
int	CanServer::getInputPortNum() const
{
	return (this->inputPortNum);
}

std::string	CanServer::getInputPasswordNum() const
{
	return (this->inputPassword);
}

int	CanServer::getPort() const
{
	return (this->port);
}

std::string CanServer::getPassWord() const
{
	return (this->password);
}

int		CanServer::getSocketFd() const
{
	return (this->socketFd);
}

struct sockaddr_in CanServer::getAddr() const{
	return(this->addr);
}

fd_set CanServer::getReads() const{
	return(this->reads);
}

fd_set CanServer::getCopyReads() const{
	return(this->copyReads);
}


std::map<int, CanClient*> *CanServer::getClientList() const{
	return(this->clientList);
}

std::map<std::string, CanChannel*> CanServer::getChannelList() const{
	return(this->channelList);
}

