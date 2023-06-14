#include "Client.hpp"

//Setter / getter

void	Client::setFd(int fd) {this->_fd = fd;}

int	Client::getFd(void) const{return (this->_fd);}

struct sockaddr_in	Client::getAddr(void) const {return this->_addr;}

// constructors / destructors

Client::Client(int fd): _fd(fd)
{
	return;
}

Client::Client( void )
{
	return;
}

Client::Client( Client const &copy)
{
	*this = copy;
}

Client  &Client::operator=( Client const &rhs)
{
	if (this == &rhs)
		return *this;
	this->_fd = rhs._fd;
	this->_addr = rhs.getAddr();
	return *this;
}

Client::~Client( void )
{
	return;
}
