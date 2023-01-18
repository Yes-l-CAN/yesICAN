#include "CanClient.hpp"
#include "CanChannel.hpp"
#include <map>
#include <utility>

CanClient::CanClient()
: nickname(), username(), realname()
{
    memset(&this->addr, 0, sizeof(this->addr));
}

CanClient::CanClient(const CanClient& ref)
{
    *this = ref;
}

CanClient& CanClient::operator=(const CanClient& ref)
{
    if (this != &ref)
    {
    }
    return (*this);
}

CanClient::~CanClient()
{
    
}

CanClient::CanClient(const struct sockaddr_in addr) : addr(addr)
{
}

void CanClient::setNickname(const std::string name)
{
    this->nickname = name;
}

std::string CanClient::getNickname(void) const
{
    return (this->nickname);
}

void CanClient::setUsername(const std::string name)
{
    this->username = name;
}

void CanClient::setMemberLevel(int lev)
{
    this->isMember = lev;
}

int CanClient::getMemberLevel(void) const
{
    return (this->isMember);
}

std::string CanClient::getUsername(void) const
{
    return (this->username);
}

void CanClient::setRealname(const std::string name)
{
    this->username = name;
}

std::string CanClient::getRealname(void) const
{
    return (this->username);
}

void CanClient::addChannelElement(std::string key, CanChannel* pNewChannel)
{

    // if (ret.second == false)
    if (this->channelList.insert(std::make_pair(key, pNewChannel)).second == false)
    {
        throw(CanClient::addChannelException());
    }
}

const char* CanClient::addChannelException::what() const throw()
{
    return "";
}
