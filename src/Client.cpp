#include "Client.hpp"

//Setter / getter

struct sockaddr_in	Client::getAddr(void) const {return this->_addr;}

int	Client::getFd(void) const{return (this->_fd);}

std::string	Client::getNick(void) const {return this->_nick;}

std::string	Client::getUser(void) const {return this->_user;}

enum status	Client::getStatus(void) const {return this->_status;}

void	Client::setFd(int fd) {this->_fd = fd;}

void	Client::setNick(std::string nick) {this->_nick = nick;}

void	Client::setUser(std::string user) {this->_user = user;}

bool	Client::setStatusUser(status newStatus){
	if (newStatus == _status + 1)
		_status = newStatus;
	else
		return (false);
	return (true);
}

// constructors / destructors

Client::Client(int fd): _status(pendingPassword), _fd(fd), _nick(), _user()
{
	return;
}

Client::Client( void ): _status(pendingPassword), _fd(), _nick(), _user()
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
