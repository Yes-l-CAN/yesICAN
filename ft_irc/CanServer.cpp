#include "./include/CanServer.hpp"

CanServer::CanServer() : socketFd(-1), maxFd(0)
{
    // Default Constructor
    setServAddr();
    FD_ZERO(&reads);
    FD_ZERO(&copyReads);

}

CanServer::~CanServer()
{
	std::map<int, CanClient*>::iterator it;
    // Destuctor
	if (this->clientList.empty() == true)
	{
		return ;
	}

	for (it = this->clientList.begin(); it != this->clientList.end(); it++)
	{
		close(it->first);
		if (it->second != NULL)
		{
			delete it->second;
		}
	}
	this->clientList.clear();
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

void CanServer::s_On(){
	try{
		s_Socket();
		setServAddr();
		s_Bind();
		s_Listen();
		setFdSet();
	} catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}
    // implement server logic here
}

void CanServer::setServAddr()
{
    this->addr.sin_family = AF_INET;
    this->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->addr.sin_port = htons(MPORT); 
}

void CanServer::findFd(){
	//너무...너무... 안 이쁜.... 넣고나니 빼는게 나을 듯 한....
	for(int i = 0; i < this->maxFd + 1; i++){
		if(FD_ISSET(i, &this->copyReads) && i == this->socketFd){
			try {
				s_Accept();
			} catch(std::exception &e) {
				std::cout << e.what() << std::endl;
				return ;
			}
		}
	}
}

void CanServer::s_Socket(){
	int	fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd < 0)
		throw (CanServer::socketCreateException());
	this->socketFd = fd;
}

void CanServer::s_Bind(){
	int		res;

	res = bind(this->socketFd, (struct sockaddr*)&(this->addr), sizeof(this->addr));
	if(res < 0)
		throw(CanServer::bindException());
}

void CanServer::s_Listen()
{
	if (listen(this->socketFd, MAX_FD) < 0)
    {
        throw(CanServer::listenException());
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
		if(res < 0)
			throw (CanServer::selectException());
		else if(res == 0)
			continue;
		else
			break;
	}
}

void CanServer::s_Accept()
{
	int clientSockFd = -1;
	struct sockaddr clientAddr;
	unsigned int size = sizeof(clientAddr);

	clientSockFd = accept(this->socketFd, (struct sockaddr*)&clientAddr, &size);
	if (clientSockFd < 0)
	{
		throw (CanServer::acceptException());
	}
	FD_SET(clientSockFd, &reads);

	CanClient *temp = new CanClient(&clientAddr);
	clientList.insert(std::make_pair(clientSockFd, temp)); 
}
// utils
void CanServer::setFdSet()
{
    fd_set* reads_addr = &this->reads;
    FD_ZERO(reads_addr);
    FD_SET(this->socketFd, reads_addr);
}

// exception
const char *CanServer::socketCreateException::what() const throw(){
	return ("can't create socket error");
}

const char *CanServer::bindException::what() const throw(){
	return ("Bind error");
}

const char *CanServer::listenException::what() const throw(){
	return ("Listen error");
}

const char *CanServer::selectException::what() const throw(){
	return ("Select error");
}

const char	*CanServer::acceptException::what() const throw() {
	return ("Accept error");
}

