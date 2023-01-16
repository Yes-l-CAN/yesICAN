#ifndef CAN_CLIENT_HPP
#define CAN_CLIENT_HPP

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

class CanClient
{
	private:
		std::string nickname;
		std::string username;
		std::string	realname;
		struct sockaddr_in addr;
		
		std::map<std::string, CanChannel*>	channelList;

	public:
		CanClient();
		CanClient(const CanClient& ref);
		CanClient(const struct sockaddr_in addr);
		CanClient& operator=(const CanClient& ref);
		~CanClient();

		void setNickname(const std::string name);
		std::string getNickname(void) const;
		void setUsername(const std::string name);
		std::string getUsername(void) const;
		void setRealname(const std::string name);
		std::string getRealname(void) const;

		void addChannelElement(const std::string key, const CanChannel *pNewChannel);

		void cSend(int fd);

		class addChannelException: public std::exception{
			virtual const char*	what() const throw();
		};

};

#endif